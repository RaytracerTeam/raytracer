/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.cpp
*/

#include "Scene/Scene.hpp"
#include "Error.hpp"
#include "Math/Algorithm.hpp"
#include "Math/Matrix44d.hpp"
#include "Math/Utils.hpp"

#include <algorithm>
#include <cmath>

namespace Raytracer {
    void Scene::addPrimitive(std::unique_ptr<IPrimitive> obj)
    {
        m_primitives.push_back(std::move(obj));
    }

    void Scene::addObj(std::unique_ptr<Obj> obj)
    {
        m_objs.push_back(std::move(obj));
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
        m_render.resize(sf::Vector2u(width, height));
    }

    void Scene::quitRenderLine(void)
    {
        m_mutex.lock();
        m_nbThreadsAlive--;
        m_mutex.unlock();
    }

    void Scene::renderLine(double imageAspectRatio, double scale, uint64_t threadNbr)
    {
        Camera &camera = getCurrentCamera();
        Dimension dimension = camera.getDimension();

        m_mutex.lock();
        size_t y = ++m_renderY;
        m_nbThreadsAlive++;
        m_mutex.unlock();

        if (y >= dimension.getHeight())
            return quitRenderLine();
        for (size_t x = 0; x < dimension.getWidth(); x++) {
            double rayX = (2 * (x + 0.5) / dimension.getWidthD() - 1) * imageAspectRatio * scale;
            double rayY = (1 - 2 * (y + 0.5) / dimension.getHeightD()) * scale;
            Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize().rotate(camera.getAngle());
            Color color = castRay(Ray(camera.getPos(), dir)) * 255.;
            if (m_renderNbr != threadNbr)
                return quitRenderLine();
            m_render.setPixel(sf::Vector2u(x, y), sf::Color(color.getR(), color.getG(), color.getB()));
        }

        std::thread(&Scene::renderLine, this, imageAspectRatio, scale, threadNbr).detach();

        quitRenderLine();
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
                m_render.setPixel(sf::Vector2u(x, y), sf::Color(color.getR(), color.getG(), color.getB()));
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

        for (const auto &obj : m_objs)
            for (const auto &tri : obj->getTriangles())
                m_readonlyPrimitives.push_back(static_cast<const IPrimitive *>(tri.get()));

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
        bool result = BVH::readBVH(ray, *m_bvhTree, intersection);
        if (!result)
            return m_skybox.getAmbientColor(ray);
        return castRayColor(ray, *intersection.primitve, intersection.rayhit);
    }

    Color Scene::getDiffuseColor(const Ray &lightRay, const RayHit &rhitPrim,
        const ILight &light, const Math::Vector3D &lightOrigin,
        const std::unique_ptr<IMaterial> &primMaterial, const Color &primColor) const
    {
        Color penombraFactor = Color(1., 1., 1.);
        BVH::Intersection intersection;

        bool hasLightHit = BVH::readBVH(lightRay, *m_bvhTree, intersection);
        if (hasLightHit && hit(intersection.rayhit, rhitPrim.getHitPoint(), lightOrigin)) {
            auto &interMaterial = intersection.primitve->getMaterial();
            penombraFactor = interMaterial->getColor(intersection.rayhit) * (1 - interMaterial->getTransparency())
                + primColor * interMaterial->getTransparency() - (1 - interMaterial->getTransparency());
            penombraFactor = Math::Algorithm::clampColor(penombraFactor);
            penombraFactor = Math::Algorithm::clampColor(penombraFactor + primMaterial->getTransparency());
        }

        double diffuse = Math::Algorithm::clampD(rhitPrim.getNormal().dot(lightRay.getDirection()), 0., 1.);
        diffuse = Math::Algorithm::clampD(diffuse + primMaterial->getTransparency(), 0., 1.);
        return primColor * light.getColor() * light.getIntensity() * diffuse * primMaterial->getDiffuse() * penombraFactor;
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

    Color Scene::castRayColor(const Ray &ray, const IPrimitive &primHit, const RayHit &rhitPrim) const
    {
        const std::unique_ptr<IMaterial> &primMaterial = primHit.getMaterial();

        // Reflection
        Color primColor = primMaterial->getColor(rhitPrim);
        if (primMaterial->getReflection() > 0) {
            if (ray.getDepth() < m_maxRayBounces) {
                auto rayScattered = primMaterial->getScatteredRay(ray, rhitPrim);
                if (rayScattered != std::nullopt)
                    primColor = primColor * (1 - primMaterial->getReflection()) + castRay(*rayScattered) * primMaterial->getReflection();
            }
        }

        // Transparency
        if (primMaterial->getTransparency() > 0) {
            if (ray.getDepth() < m_maxRayBounces) {
                std::optional<Ray> rayTransparency;
                if (primMaterial->getRefraction() != 0)
                    rayTransparency = primMaterial->getTransparencyRefractionRay(ray, rhitPrim);
                else
                    rayTransparency = primMaterial->getTransparencyRay(ray, rhitPrim);
                if (rayTransparency != std::nullopt)
                    primColor = primColor * (1 - primMaterial->getTransparency()) + castRay(*rayTransparency) * primMaterial->getTransparency();
                else
                    primColor = Color(1., 0, 1);
            }
        }

        // -- Ambient Light --
        Color ambientColor(0., 0, 0);
        for (const auto &ambientLight : m_lightSystem.getAmbientLights()) {
            if (!ambientLight->isShown())
                continue;
            ambientColor += primColor * ambientLight->getColor() * ambientLight->getIntensity();
        }

        // -- Diffuse Light -- && -- Specular Light --
        Color diffuseColor(0., 0, 0);
        Color specularColor(0., 0, 0);

        // Directional light
        for (const auto &dLight : m_lightSystem.getDirectionalLights()) {
            if (!dLight->isShown())
                continue;
            Ray dirRay = Ray(rhitPrim.getHitPoint(), dLight->getDirection());
            Color dPenombraFactor = Color(1., 1., 1.);

            diffuseColor += getDiffuseColor(dirRay, rhitPrim, *dLight,
                Math::Vector3D(0, 0, 0), primMaterial, primColor);
            if (primMaterial->getSpecular() > 0)
                specularColor += primMaterial->getSpecular(dLight.get(),
                    rhitPrim.getNormal(), dLight->getDirection().normalize(), ray);
        }

        // Point lights
        for (const auto &light : m_lightSystem.getLights()) {
            if (!light->isShown())
                continue;
            auto lightVec = light->getOrigin() - rhitPrim.getHitPoint();
            auto lightDirection = lightVec.normalize();
            Ray lightRay = Ray(rhitPrim.getHitPoint(), lightDirection);

            diffuseColor += getDiffuseColor(lightRay, rhitPrim, *light,
                light->getOrigin(), primMaterial, primColor);
            if (primMaterial->getSpecular() > 0)
                specularColor += primMaterial->getSpecular(light.get(),
                    rhitPrim.getNormal(), lightDirection, ray);
        }

        return ambientColor + diffuseColor + specularColor;
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

    void Scene::removeObj(size_t index)
    {
        if (index >= m_objs.size())
            return;
        m_objs.erase(m_objs.begin() + index);
    }

    void Scene::showCurrentRenderedLine(void)
    {
        if (m_renderY >= m_render.getSize().y)
            return;
        for (size_t x = 0; x < m_render.getSize().x; x++)
            m_render.setPixel(sf::Vector2u(x, m_renderY + 1), m_render.getPixel(sf::Vector2u(x, m_renderY + 1)) * sf::Color(100, 100, 100));
    }

    std::optional<BVH::Intersection> Scene::getIntersectionHit(sf::Vector2i mousePos) const {
        Camera &camera = getCurrentCamera();
        Dimension dimension = camera.getDimension();
        double scale = std::tan(Math::deg2rad(camera.getFov() * 0.5));
        double imageAspectRatio = dimension.getWidthD() / dimension.getHeightD();

        double rayX = (2 * (mousePos.x + 0.5) / dimension.getWidthD() - 1) * imageAspectRatio * scale;
        double rayY = (1 - 2 * (mousePos.y + 0.5) / dimension.getHeightD()) * scale;
        Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize().rotate(camera.getAngle());
        Ray ray = Ray(camera.getPos(), dir);

        BVH::Intersection intersection;
        auto result = BVH::readBVH(ray, *m_bvhTree, intersection);
        if (!result)
            return std::nullopt;
        return intersection;
    }

    std::optional<const IPrimitive *> Scene::getPrimitiveHit(sf::Vector2i mousePos) const
    {
        std::optional<BVH::Intersection> intersection = getIntersectionHit(mousePos);
        if (!intersection.has_value())
            return std::nullopt;
        return intersection->primitve;

    }

    void Scene::killObjects(void)
    {
        for (std::size_t i = 0; i < m_primitives.size(); i++) {
            if (m_primitives[i]->getDieASAP()) {
                removePrimitive(i);
                i--;
            }
        }
        for (std::size_t i = 0; i < m_lightSystem.getLights().size(); i++) {
            if (m_lightSystem.getLights()[i]->getDieASAP()) {
                m_lightSystem.removeLight(i);
                i--;
            }
        }
        for (std::size_t i = 0; i < m_lightSystem.getAmbientLights().size(); i++) {
            if (m_lightSystem.getAmbientLights()[i]->getDieASAP()) {
                m_lightSystem.removeAmbientLight(i);
                i--;
            }
        }
        for (std::size_t i = 0; i < m_lightSystem.getDirectionalLights().size(); i++) {
            if (m_lightSystem.getDirectionalLights()[i]->getDieASAP()) {
                m_lightSystem.removeDirectionalLight(i);
                i--;
            }
        }
        for (std::size_t i = 0; i < m_objs.size(); i++) {
            if (m_objs[i]->getDieASAP()) {
                removeObj(i);
                i--;
            }
        }
    }
    void Scene::reset(void)
    {
        for (auto &prim : m_primitives)
            prim->dieASAP();
        for (auto &light : m_lightSystem.getLights())
            light->dieASAP();
        for (auto &ambientLight : m_lightSystem.getAmbientLights())
            ambientLight->dieASAP();
        for (auto &dirLight : m_lightSystem.getDirectionalLights())
            dirLight->dieASAP();
        for (auto &obj : m_objs)
            obj->dieASAP();
        m_cameras.clear();
    }

    void Scene::waitRendering(size_t nbImages, size_t maxImage)
    {
        if (maxImage != 0)
            std::cout << "Image n°" << nbImages + 1 << "/" << maxImage << '\n';
        while (getNbThreadsAlive() > 0) {
            int percent = (getRenderY() / getCurrentCamera().getDimension().getHeightD()) * 100;

            std::cout << "Rendering... ";
            std::cout << "\033[1;37m[";
            for (int i = 0; i < percent / 4; i++)
                std::cout << "\033[1;32m=";
            for (int i = percent / 4; i < 25; i++)
                std::cout << "\033[1;37m ";
            std::cout << "\033[1;37m] ";

            std::cout << "\033[1;36m" << percent << "%\r\033[0m" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "\033[1A";
        std::cout << "\033[K";
    }

    #ifdef BONUSCAMERA
    void Scene::initRealCamera(void)
    {
        m_realCamera.init();
    }

    void Scene::updateRealCamera(void)
    {
        m_realCamera.update();
    }
    #endif
} // namespace Raytracer
