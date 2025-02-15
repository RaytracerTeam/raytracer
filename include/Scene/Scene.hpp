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
#include "Scene/Keyframe.hpp"

#include "Scene/Primitives/Obj.hpp"
#include "Scene/Inventory.hpp"

#ifdef BONUSCAMERA
    #include "RealCamera.hpp"
#endif

namespace Raytracer {
    #define DEFAULT_SKYBOX "assets/skyboxes/sky.jpg"
    #define SCREEN_RATIO 16.0f / 9.0f
    #define DEFAULT_MOVEMENT_SPEED 0.3f
    #define DEFAULT_ROTATION_SPEED 3
    class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        void addPrimitive(std::unique_ptr<IPrimitive> obj);
        void addObj(std::unique_ptr<Obj> obj);
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
        void setMaxRayBounces(size_t maxRayBounces) { m_maxRayBounces = maxRayBounces; }
        void setBvhMaxPrimLimit(size_t maxPrimLimit) { m_bvhMaxPrimLimit = maxPrimLimit; }
        void setAlwaysRender(bool alwaysRender) { m_alwaysRender = alwaysRender; }
        void setCameraSpeed(float cameraSpeed) { m_cameraSpeed = cameraSpeed; }
        void setCameraSensitivity(float cameraSensitivity) { m_cameraSensitivity = cameraSensitivity; }

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
        size_t getMaxRayBounces(void) const { return m_maxRayBounces; }
        size_t getBvhMaxPrimLimit(void) const { return m_bvhMaxPrimLimit; }
        bool getAlwaysRender(void) const { return m_alwaysRender; }
        float getCameraSpeed(void) const { return m_cameraSpeed; }
        float getCameraSensitivity(void) const { return m_cameraSensitivity; }
        std::vector<std::unique_ptr<Obj>> &getObjs(void) { return m_objs; }
        const std::vector<std::unique_ptr<Obj>> &getObjs(void) const { return m_objs; }
        Inventory &getInventory(void) { return m_inventory; }
        const Inventory &getInventory(void) const { return m_inventory; }

        void setRenderPixel(size_t x, size_t y, const Color &color) {
            m_render.setPixel(sf::Vector2u(x, y), sf::Color(color.getR() * 255, color.getG() * 255, color.getB() * 255));
        }

        const std::vector<Keyframe> &getCameraKeyframes(void) const { return m_vecKeyframes; }
        size_t getKeyframesTick(void) const { return m_tickKeyframes; }
        void addKeyframe(const Keyframe &keyframe) { m_vecKeyframes.push_back(keyframe); }
        void setKeyframesTick(size_t tickrate) { m_tickKeyframes = tickrate; }

        void resizeRender(unsigned int width, unsigned int height);
        void updatePrimitives(void);
        void removePrimitive(size_t index);
        void removeLight(size_t index);
        bool removeCamera(size_t index);
        void removeObj(size_t index);
        void reset(void);

        void showCurrentRenderedLine(void);
        std::optional<BVH::Intersection> getIntersectionHit(sf::Vector2i mousePos) const;
        std::optional<const IPrimitive *> getPrimitiveHit(sf::Vector2i mousePos) const;

        void killObjects(void);
        Color getDiffuseColor(const Ray &lightRay, const RayHit &rhitPrim,
            const ILight &light, const Math::Vector3D &lightOrigin,
            const std::unique_ptr<IMaterial> &primMaterial, const Color &primColor) const;
        #ifdef BONUSCAMERA
        void initRealCamera(void);
        void updateRealCamera(void);
        RealCamera &getRealCamera(void) { return m_realCamera; }
        #endif

        void waitRendering(size_t nbImages = 0, size_t maxImage = 0);

    private:
        Color castRayColor(const Ray &ray, const IPrimitive &primHit, const RayHit &rhitPrim) const;
        Color castRay(const Ray &ray) const;
        bool hit(const std::optional<RayHit> &rayHit, const Math::Vector3D &objOrigin, const Math::Vector3D &objTarget) const;

        std::vector<std::unique_ptr<IPrimitive>> m_primitives;
        // useful to copy the vector around.
        std::vector<const IPrimitive *> m_readonlyPrimitives;

        std::vector<std::unique_ptr<Obj>> m_objs;
        Inventory m_inventory;

        std::unique_ptr<BVH::Node> m_bvhTree;
        size_t m_bvhMaxPrimLimit = 5; // temp : get via optimisation

        std::vector<std::unique_ptr<Camera>> m_cameras;
        size_t m_curCamIndex = 0;

        SceneLightning m_lightSystem;

        Skybox m_skybox = Skybox(std::make_unique<MaterialTexture>(), SkyboxUVType::SPHERE);
        size_t m_maxRayBounces = 5;
        // double m_maxDropShadowsRay = 1;

        bool m_renderLights = false;

        const size_t m_maxNbThreads = std::thread::hardware_concurrency();
        size_t m_nbThreads = m_maxNbThreads;
        size_t m_nbThreadsAlive = 0;
        std::mutex m_mutex;

        sf::Image m_render;
        uint64_t m_renderNbr = 0;
        size_t m_renderY;

        bool m_alwaysRender = false;
        float m_cameraSpeed = DEFAULT_MOVEMENT_SPEED;
        float m_cameraSensitivity = DEFAULT_ROTATION_SPEED;

        std::vector<Keyframe> m_vecKeyframes;
        size_t m_tickKeyframes;

        // Bonus Real camera
        #ifdef BONUSCAMERA
        RealCamera m_realCamera;
        #endif
    };
}
