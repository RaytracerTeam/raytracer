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

#include "IPrimitive.hpp"
#include "Camera.hpp"

namespace Raytracer {
    class Scene {
        public:
            Scene() = default;
            ~Scene() = default;

            void addPrimitive(std::unique_ptr<IPrimitive> obj);
            void addCamera(std::unique_ptr<Camera> obj);

            std::vector<bool> render(void);

            bool setCameraIndex(size_t index);
            bool setCameraIndexRelative(int64_t offset);

            Camera *getCurrentCamera(void) const {
                if (m_cameras.size() == 0)
                    return nullptr;
                return m_cameras.at(m_curCamIndex).get();
            }

        private:
            bool castRay(const Ray &ray);

            std::list<std::unique_ptr<IPrimitive>> m_primitives;
            std::vector<std::unique_ptr<Camera>> m_cameras;
            size_t m_curCamIndex = 0;
    };
}
