/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneLightning.hpp
*/

#pragma once

#include "Scene/Lights/DirectionalLight.hpp"
#include "Scene/Lights/PointLight.hpp"

#include <memory>
#include <vector>

namespace Raytracer {
    class SceneLightning {
    public:
        SceneLightning(const Math::Vector3D &dir, const Color &color, double globalIllumination = 0.26)
            : m_dirLight(dir, color, globalIllumination)
        {
        }

        std::vector<std::unique_ptr<PointLight>> const &getLights(void) const { return m_lights; }
        std::vector<std::unique_ptr<PointLight>> &getLights(void) { return m_lights; }


        void addLight(std::unique_ptr<PointLight> obj)
        {
            m_lights.push_back(std::move(obj));
        }

        void removeLight(size_t index)
        {
            if (index >= m_lights.size())
                return;
            m_lights.erase(m_lights.begin() + index);
        }

        const DirectionalLight &getDirectionLight(void) const { return m_dirLight; }
        void setDirectionLight(const DirectionalLight &direction) { m_dirLight = direction; }

    private:
        std::vector<std::unique_ptr<PointLight>> m_lights;
        DirectionalLight m_dirLight;
    };
} // namespace Raytracer
