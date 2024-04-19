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

#include "Scene/Camera.hpp"
#include "Color.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Scene/Light.hpp"

namespace Raytracer {
    class Scene {
    public:
        Scene() = default;
        ~Scene() = default;

        void addPrimitive(std::unique_ptr<IPrimitive> obj);
        void addCamera(std::unique_ptr<Camera> obj);
        void addLight(std::unique_ptr<Light> obj);

        std::vector<Color> render(void);

        bool setCameraIndex(size_t index);
        bool setCameraIndexRelative(int64_t offset);

        Camera &getCurrentCamera(void) const;
        void updatePrimitives(void);
    private:
        Color castRay(const Ray &ray) const;

        std::vector<std::unique_ptr<IPrimitive>> m_primitives;
        std::vector<std::unique_ptr<Camera>> m_cameras;
        std::vector<std::unique_ptr<Light>> m_lights;
        size_t m_curCamIndex = 0;
    };
}
