/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Animation.hpp
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Scene/Keyframe.hpp"
#include "Writer.hpp"

#include <memory>
#include <functional>

namespace Raytracer {
    class Animation {
        public:
            Animation(const std::string &path, std::unique_ptr<Scene> scene, const Dimension &dim);
            ~Animation() = default;

            void render(WriteFile::WriteType type);
        private:
            void screenshot(Camera &camera, const Keyframe &keyframe,
                const Math::Vector3D &curVec, const Math::Angle3D &angle, double tick,
                size_t iteration, WriteFile::WriteType type);

            const std::string m_path;
            std::unique_ptr<Scene> m_scene;
            const Dimension m_dim;
    };
} // namespace Raytracer
