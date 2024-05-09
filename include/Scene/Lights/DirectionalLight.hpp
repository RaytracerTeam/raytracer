/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** DirectionalLight.hpp
*/

#pragma once

#include "ALight.hpp"

namespace Raytracer {
    class DirectionalLight : public ALight {
    public:
        DirectionalLight(const Math::Vector3D &direction, const Color &color = {255U, 255, 255}, double intensity = 1.)
            : ALight(color, intensity)
            , m_direction(direction)
        {
        }
        ~DirectionalLight() = default;

        LightType getType(void) const override { return LightType::DIRECTIONAL; }

        const Math::Vector3D &getDirection(void) const { return m_direction; }
        void setDirection(const Math::Vector3D &direction) { m_direction = direction; }

    private:
        Math::Vector3D m_direction;
    };
}
