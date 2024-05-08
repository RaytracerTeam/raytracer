/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.cpp
*/

#include "Scene/Scene.hpp"
#include "Error.hpp"
#include "Math/Algorithm.hpp"
#include "Math/Utils.hpp"
#include "Math/Matrix44d.hpp"

#include <algorithm>
#include <cmath>

namespace Raytracer {
    // todo : direction should be in parsing
    Scene::Scene()
        : m_lightSystem({ -1, 1, -1 }, { 200U, 200, 200 })
    {
    }

    void Scene::addPrimitive(std::unique_ptr<IPrimitive> obj)
    {
        m_primitives.push_back(std::move(obj));
    }

    void Scene::addCamera(std::unique_ptr<Camera> obj)
    {
        m_cameras.push_back(std::move(obj));
    }

    void Scene::addLight(std::unique_ptr<PointLight> obj)
    {
        m_lightSystem.addLight(std::move(obj));
    }

    bool Scene::setCameraIndex(size_t index)
    {
        if (index >= m_cameras.size())
            return false;
        m_curCamIndex = index;
        return true;
    }

    bool Scene::setCameraIndexRelative(int64_t offset)
    {
        if ((size_t)(std::abs(offset)) >= m_curCamIndex)
            return false;
        m_curCamIndex += offset;
        return true;
    }

    Camera &Scene::getCurrentCamera(void) const
    {
        if (m_cameras.size() == 0)
            throw Error("There is no camera available", "Scene::getCurrentCamera");
        return *m_cameras.at(m_curCamIndex).get();
    }

    size_t Scene::getCameraCount(void) const
    {
        return m_cameras.size();
    }

    void Scene::resizeRender(unsigned int width, unsigned int height)
    {
        m_render.create(width, height);
    }

    void Scene::renderLine(double imageAspectRatio, double scale, uint64_t threadNbr)
    {
        Camera &camera = getCurrentCamera();
        Dimension dimension = camera.getDimension();

        m_mutex.lock();
        size_t y = ++m_renderY;
        m_mutex.unlock();

        if (y >= dimension.getHeight())
            return;
        for (size_t x = 0; x < dimension.getWidth(); x++) {
            double rayX = (2 * (x + 0.5) / dimension.getWidthD() - 1) * imageAspectRatio * scale;
            double rayY = (1 - 2 * (y + 0.5) / dimension.getHeightD()) * scale;
            Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize().rotate(camera.getAngle());
            Color color = castRay(Ray(camera.getPos(), dir)) * 255.;
            if (m_renderNbr != threadNbr)
                return;
            m_render.setPixel(x, y, sf::Color(color.getR(), color.getG(), color.getB()));
        }

        std::thread(&Scene::renderLine, this, imageAspectRatio, scale, threadNbr).detach();
    }

    void Scene::render(void)
    {
        thread_local uint64_t threadNbr = ++m_renderNbr;

        Camera &camera = getCurrentCamera();
        Dimension dimension = camera.getDimension();

        double scale = std::tan(Math::deg2rad(camera.getFov() * 0.5));
        double imageAspectRatio = dimension.getWidthD() / dimension.getHeightD();

        m_renderY = -1;
        for (size_t i = 0; i < m_nbThreads - 1; i++)
            std::thread(&Scene::renderLine, this, imageAspectRatio, scale, threadNbr).detach();
    }

    void Scene::renderWhitoutThread(void)
    {
        Camera &camera = getCurrentCamera();
        Dimension dimension = camera.getDimension();

        double scale = std::tan(Math::deg2rad(camera.getFov() * 0.5));
        double imageAspectRatio = dimension.getWidthD() / dimension.getHeightD();

        for (size_t y = 0; y < dimension.getHeight(); y++) {
            for (size_t x = 0; x < dimension.getWidth(); x++) {
                double rayX = (2 * (x + 0.5) / dimension.getWidthD() - 1) * imageAspectRatio * scale;
                double rayY = (1 - 2 * (y + 0.5) / dimension.getHeightD()) * scale;
                Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize().rotate(camera.getAngle());
                Color color = castRay(Ray(camera.getPos(), dir)) * 255.;
                m_render.setPixel(x, y, sf::Color(color.getR(), color.getG(), color.getB()));
            }
        }
    }

    /* call this whenever the object move posititon */
    void Scene::updatePrimitives(void)
    {
        m_readonlyPrimitives = std::vector<const IPrimitive *>();
        m_readonlyPrimitives.reserve(m_primitives.size());
        for (const auto &prim : m_primitives)
            m_readonlyPrimitives.push_back(static_cast<const IPrimitive *>(prim.get()));

        m_bvhTree = BVH::createBVH(m_bvhMaxPrimLimit, m_readonlyPrimitives, BVH::axisAligned);
    }

    Color Scene::castRay(const Ray &ray) const
    {
        Math::Matrix44 mat;
        if (m_renderLights) {
            for (const auto &light : m_lightSystem.getLights()) {
                if (!light->isShown())
                    continue;
                std::optional<RayHit> rayhit = light->hit(ray);
                if (rayhit == std::nullopt)
                    continue;
                return light->getColor();
            }
        }
        BVH::Intersection intersection;
        auto result = BVH::readBVH(ray, *m_bvhTree, intersection);
        if (!result)
            return m_skybox.getAmbientColor(ray);
        return castRayColor(ray, intersection.primitve, intersection.rayhit);
    }

    double Scene::shadowPenombra(const Ray &lightRay, const IPrimitive *primHit, const PointLight &pointLight) const
    {
        double nbShadowRays = 0;
        double radius = pointLight.getRadius();
        const double offset = 1 / m_maxDropShadowsRay;

        for (double i = -0.5; i <= 0.5; i += offset) {
            double val = i * radius;
            auto ray = Ray(lightRay.getOrigin(), (lightRay.getDirection() + val));
            bool shadowed = false;

            for (const auto &prim : m_primitives) {
                if (primHit == prim.get())
                    continue;
                auto shadowHit = prim->hit(ray);
                if (shadowHit != std::nullopt) {
                    if (shadowHit->getDistance() * shadowHit->getDistance() < 0.001)
                        continue;
                    if (
                        Math::Vector3D::gDist(ray.getOrigin(), shadowHit->getHitPoint())
                        >= Math::Vector3D::gDist(ray.getOrigin(), pointLight.getOrigin()))
                        continue;
                    shadowed = true;
                    break;
                }
            }
            if (!shadowed && pointLight.hit(ray) != std::nullopt)
                nbShadowRays++;
        }
        return nbShadowRays / m_maxDropShadowsRay;
    }

    bool Scene::hit(const std::optional<RayHit> &rayHit, const Math::Vector3D &objOrigin, const Math::Vector3D &objTarget) const
    {
        if (rayHit == std::nullopt)
            return false;
        if ( // even if the ray touches something, that doesn't mean it's before the light.
            Math::Vector3D::gDist(objOrigin, rayHit->getHitPoint())
            < Math::Vector3D::gDist(objOrigin, objTarget))
            return true;
        return false;
    }

    Color Scene::castRayColor(const Ray &ray, const IPrimitive *primHit, const RayHit &rhitPrim) const
    {
        Color color;
        IMaterial *primMaterial = primHit->getMaterial();
        auto &dirLight = m_lightSystem.getDirectionLight();

        // Reflections
        Color primColor = primMaterial->getColor(rhitPrim);
        if (primMaterial->getAlbedo() > 0) {
            if (ray.getDepth() < m_maxRayBounces) {
                auto rayScattered = primMaterial->getScatteredRay(ray, rhitPrim);
                if (rayScattered != std::nullopt)
                    primColor *= castRay(*rayScattered) * primMaterial->getAlbedo();
            }
        }

        // Directional light
        auto dirRay = Ray(rhitPrim.getHitPoint(), (dirLight.getDirection()));
        BVH::Intersection intersection;
        auto hasLightHit = BVH::readBVH(dirRay, *m_bvhTree, intersection);
        if (!hasLightHit) {
            auto dirLightDiffuse = Math::Algorithm::clampD(rhitPrim.getNormal().dot(dirLight.getDirection()), 0., 1.);
            color += primColor * (dirLight.getColor() * dirLightDiffuse * dirLight.getIntensity());
        }

        // Point lights
        for (const auto &light : m_lightSystem.getLights()) {
            if (!light->isShown())
                continue;
            auto lightVec = light->getOrigin() - rhitPrim.getHitPoint();
            auto lightDirection = lightVec.normalize();
            Ray lightRay = Ray(rhitPrim.getHitPoint(), lightDirection);
            double penombraFactor = 1.;

            BVH::Intersection intersection;
            auto hasLightHit = BVH::readBVH(lightRay, *m_bvhTree, intersection);
            if (hasLightHit && hit(intersection.rayhit, rhitPrim.getHitPoint(), light->getOrigin())) {
                if (m_maxDropShadowsRay > 1)
                    penombraFactor = shadowPenombra(lightRay, primHit, *light);
                else
                    penombraFactor = 0;
                break;
            }

            auto diffuse = Math::Algorithm::clampD(rhitPrim.getNormal().dot(lightDirection), 0., 1.);
            if (primMaterial->hasPhong()) {
                primColor += primMaterial->getSpecular(light.get(), rhitPrim, lightDirection);
            }
            color += primColor * (light->getColor() * diffuse * penombraFactor * light->getIntensity());
        }
        color += primColor * m_ambientLightColor * m_ambientLightIntensity;
        return color;
    }
    void Scene::setSkyboxPath(const std::string &path)
    {
        m_skybox.setMaterialTexture(std::make_unique<MaterialTexture>(path));
    }

    void Scene::removePrimitive(size_t index)
    {
        if (index >= m_primitives.size())
            return;
        m_primitives.erase(m_primitives.begin() + index);
    }
    void Scene::removeLight(size_t index)
    {
        m_lightSystem.removeLight(index);
    }
    // return false if the index is out of range
    bool Scene::removeCamera(size_t index)
    {
        if (index >= m_cameras.size())
            return false;
        m_cameras.erase(m_cameras.begin() + index);
        return true;
    }
} // namespace Raytracer
