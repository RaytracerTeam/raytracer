/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneLightning.hpp
*/

#pragma once

#include "Scene/Interfaces/ILight.hpp"

#include <vector>
#include <memory>

namespace Raytracer {
    class SceneLightning {
        public:
            SceneLightning(const double globalIllumination = 0.26)
            : m_gIllumination(globalIllumination)
            {}

            std::vector<std::unique_ptr<ILight>> const &getLights(void) const { return m_lights; }
            double getGlobalIllumination(void) const { return m_gIllumination; }

            void addLight(std::unique_ptr<ILight> obj)
            {
                m_lights.push_back(std::move(obj));
            }
        private:
            std::vector<std::unique_ptr<ILight>> m_lights;
            double m_gIllumination;
    };
} // namespace Raytracer
