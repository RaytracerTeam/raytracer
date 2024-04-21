/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.h
*/

#pragma once

#include <list>
#include <memory>
#include <vector>

#include "Color.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Interfaces/ILight.hpp"
#include "Scene/Interfaces/IPrimitive.hpp"
#include "Scene/SceneLightning.hpp"

namespace Raytracer {
    class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        void addPrimitive(std::unique_ptr<IPrimitive> obj);
        void addCamera(std::unique_ptr<Camera> obj);
        void addLight(std::unique_ptr<ILight> obj);

        std::vector<Color> render(void);

        bool setCameraIndex(size_t index);
        bool setCameraIndexRelative(int64_t offset);

        Camera &getCurrentCamera(void) const;
        void updatePrimitives(void);

    private:
        Color castRayColor(const Ray &ray, const IPrimitive *primHit, const RayHit &rhitPrim) const;
        Color castRay(const Ray &ray) const;

        std::vector<std::unique_ptr<IPrimitive>> m_primitives;
        std::vector<std::unique_ptr<Camera>> m_cameras;
        size_t m_curCamIndex = 0;

        SceneLightning m_lightSystem;
        // size_t m_maxRayBounces = 5; // todo : set in config
    };
}
