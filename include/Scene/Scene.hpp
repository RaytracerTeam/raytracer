/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.h
*/

#pragma once

#include <list>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>

#include "Color.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Interfaces/ILight.hpp"
#include "Scene/Interfaces/IPrimitive.hpp"
#include "Scene/SceneLightning.hpp"
#include "Skybox.hpp"
#include "Optimisation/BVH.hpp"

namespace Raytracer {
    #define DEFAULT_SKYBOX "assets/skyboxes/sky.jpg"
    #define SCREEN_RATIO 16.0f / 9.0f
    class Scene {
    public:
        Scene();
        ~Scene() = default;

        void addPrimitive(std::unique_ptr<IPrimitive> obj);
        void addCamera(std::unique_ptr<Camera> obj);
        void addLight(std::unique_ptr<PointLight> obj);

        void render(void);
        void renderLine(double imageAspectRatio, double scale, uint64_t threadNbr);
        void quitRenderLine(void);
        void renderWhitoutThread(void);

        bool setCameraIndex(size_t index);
        bool setCameraIndexRelative(int64_t offset);
        void setSkyboxPath(const std::string &path);
        void setRenderLights(bool renderLights) { m_renderLights = renderLights; }
        void setRenderNbr(uint64_t nbr) { m_renderNbr = nbr; }
        void setNbThreads(size_t nbThreads) { m_nbThreads = nbThreads; }

        Camera &getCurrentCamera(void) const;
        const std::vector<std::unique_ptr<Camera>> &getCameras(void) const { return m_cameras; }
        size_t getCameraCount(void) const;
        std::vector<std::unique_ptr<IPrimitive>> &getPrimitives(void) { return m_primitives; }
        const std::vector<std::unique_ptr<IPrimitive>> &getPrimitives(void) const { return m_primitives; }
        const std::vector<std::unique_ptr<PointLight>> &getLights(void) const { return m_lightSystem.getLights(); }
        std::vector<std::unique_ptr<PointLight>> &getLights(void) { return m_lightSystem.getLights(); }
        SceneLightning &getLightSystem(void) { return m_lightSystem; }
        const SceneLightning &getLightSystem(void) const { return m_lightSystem; }
        bool getRenderLights(void) const { return m_renderLights; }
        Skybox &getSkybox(void) { return m_skybox; }
        const Skybox &getSkybox(void) const { return m_skybox; }
        std::string getSkyboxPath(void) const { return m_skybox.getMaterialTexture()->getPathname(); }
        Color getSkyboxColor(void) const { return m_skybox.getAmbientColor(); }
        const sf::Image &getRender(void) const { return m_render; }
        uint64_t getRenderNbr(void) const { return m_renderNbr; }
        size_t getNbThreads(void) const { return m_nbThreads; }
        size_t getMaxNbThreads(void) const { return m_maxNbThreads; }
        size_t getNbThreadsAlive(void) const { return m_nbThreadsAlive; }
        size_t getRenderY(void) const { return m_renderY; }

        void resizeRender(unsigned int width, unsigned int height);
        void updatePrimitives(void);
        void removePrimitive(size_t index);
        void removeLight(size_t index);
        bool removeCamera(size_t index);

        void showCurrentRenderedLine(void) {
            if (m_renderY >= m_render.getSize().y)
                return;
            for (size_t x = 0; x < m_render.getSize().x; x++)
                m_render.setPixel(x, m_renderY + 1, m_render.getPixel(x, m_renderY + 1) * sf::Color(100, 100, 100));
        }

    private:
        Color castRayColor(const Ray &ray, const IPrimitive *primHit, const RayHit &rhitPrim) const;
        Color castRay(const Ray &ray) const;
        double shadowPenombra(const Ray &lightRay, const IPrimitive *primHit, const PointLight &pointLight) const;
        bool hit(const std::optional<RayHit> &rayHit, const Math::Vector3D &objOrigin, const Math::Vector3D &objTarget) const;

        std::vector<std::unique_ptr<IPrimitive>> m_primitives;
        // useful to copy the vector around.
        std::vector<const IPrimitive *> m_readonlyPrimitives;

        std::unique_ptr<BVH::Node> m_bvhTree;
        size_t m_bvhMaxPrimLimit = 5; // temp : get via optimisation

        std::vector<std::unique_ptr<Camera>> m_cameras;
        size_t m_curCamIndex = 0;

        SceneLightning m_lightSystem;

        Skybox m_skybox = Skybox(std::make_unique<MaterialTexture>(DEFAULT_SKYBOX), SPHERE);
        size_t m_maxRayBounces = 5; // todo : set in config
        double m_maxDropShadowsRay = 1; // todo : set in config

        bool m_renderLights = false;

        const size_t m_maxNbThreads = std::thread::hardware_concurrency();
        size_t m_nbThreads = m_maxNbThreads;
        size_t m_nbThreadsAlive = 0;
        std::mutex m_mutex;

        sf::Image m_render;
        uint64_t m_renderNbr = 0;
        size_t m_renderY;
    };
}
