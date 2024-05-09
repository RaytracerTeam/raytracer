/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneLightning.hpp
*/

#pragma once

#include "Scene/Lights/DirectionalLight.hpp"
#include "Scene/Lights/PointLight.hpp"
#include "Scene/Lights/AmbientLight.hpp"

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
        const DirectionalLight &getDirectionLight(void) const { return m_dirLight; }
        std::vector<std::unique_ptr<AmbientLight>> const &getAmbientLights(void) const { return m_ambientLights; }
        std::vector<std::unique_ptr<AmbientLight>> &getAmbientLights(void) { return m_ambientLights; }

        void setDirectionLight(const DirectionalLight &direction) { m_dirLight = direction; }

        void addAmbientLight(std::unique_ptr<AmbientLight> obj)
        {
            m_ambientLights.push_back(std::move(obj));
        }
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
        void removeAmbientLight(size_t index)
        {
            if (index >= m_ambientLights.size())
                return;
            m_ambientLights.erase(m_ambientLights.begin() + index);
        }


    private:
        std::vector<std::unique_ptr<PointLight>> m_lights;
        DirectionalLight m_dirLight;
        std::vector<std::unique_ptr<AmbientLight>> m_ambientLights;
    };
} // namespace Raytracer
