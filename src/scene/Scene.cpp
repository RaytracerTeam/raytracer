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

    // https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
    std::vector<Color> Scene::render(void)
    {
        Camera &camera = getCurrentCamera();
        Dimension dimension = camera.getDimension();

        std::vector<Color> buffer(dimension.getHeight() * dimension.getWidth());
        size_t curPosBuffer = 0;

        double scale = std::tan(Math::deg2rad(camera.getFov() * 0.5));
        double imageAspectRatio = dimension.getWidthD() / dimension.getHeightD();

        for (size_t y = 0; y < dimension.getHeight(); y++) {
            for (size_t x = 0; x < dimension.getWidth(); x++) {
                double rayX = (2 * (x + 0.5) / dimension.getWidthD() - 1) * imageAspectRatio * scale;
                double rayY = (1 - 2 * (y + 0.5) / dimension.getHeightD()) * scale;
                Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize().rotate(camera.getAngle());
                buffer[curPosBuffer++] = castRay(Ray(camera.getPos(), dir));
            }
        }
        return buffer;
    }

    /* call this whenever the object move posititon */
    void Scene::updatePrimitives(void)
    {
        m_readonlyPrimitives = std::vector<const IPrimitive *>();
        m_readonlyPrimitives.reserve(m_primitives.size());
        for (const auto &prim : m_primitives)
            m_readonlyPrimitives.push_back(static_cast<const IPrimitive *>(prim.get()));

        m_bvhTree = BVH::createBVH(5, m_readonlyPrimitives, BVH::axisAligned);
    }

    Color Scene::castRay(const Ray &ray) const
    {
        if (m_renderLights) {
            for (const auto &light : m_lightSystem.getLights()) {
                std::optional<RayHit> rayhit = light->hit(ray);
                if (rayhit == std::nullopt)
                    continue;
                return light->getColor();
            }
        }
        auto result = BVH::readBVH(ray, *m_bvhTree);
        if (result == std::nullopt)
            return m_skybox.getAmbientColor(ray);
        return castRayColor(ray, result->second, result->first);
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

    bool Scene::hit(const std::optional<RayHit> &rayHit) const
    {
        if (rayHit == std::nullopt)
            return false;
        if (rayHit->getDistance() * rayHit->getDistance() < 0.001)
            return false;
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
        auto lightHit = BVH::readBVH(dirRay, *m_bvhTree);
        if (!hit(lightHit->first)) {
            auto dirLightDiffuse = Math::Algorithm::clampD(rhitPrim.getNormal().dot(dirLight.getDirection()), 0., 1.);
            color += primColor * (dirLight.getColor() * dirLightDiffuse * dirLight.getIntensity());
        }

        // Point lights
        for (const auto &light : m_lightSystem.getLights()) {
            auto lightVec = light->getOrigin() - rhitPrim.getHitPoint();
            auto lightDirection = lightVec.normalize();
            Ray lightRay = Ray(rhitPrim.getHitPoint(), lightDirection);
            double penombraFactor = 1.;

            auto lightHit = BVH::readBVH(lightRay, *m_bvhTree);
            if (hit(lightHit->first)) {
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
    bool Scene::removeCamera(size_t index)
    {
        if (index >= m_cameras.size())
            return false;
        m_cameras.erase(m_cameras.begin() + index);
        if (m_cameras.size() == 0) {
            m_cameras.push_back(std::make_unique<Camera>());
            return true;
        }
        return false;
    }
} // namespace Raytracer
