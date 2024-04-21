/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** PointLight.hpp
*/

#pragma once

#include "ALight.hpp"

namespace Raytracer {
    class PointLight : public ALight {
    public:
        PointLight(const Math::Vector3D &origin)
            : ALight(origin)
        {
        }
        PointLight(const Math::Vector3D &origin, const Color &color)
            : ALight(origin, color)
        {
        }
        PointLight(const Math::Vector3D &origin, const Color &color, double diffuse)
            : ALight(origin, color, diffuse)
        {
        }
        ~PointLight() = default;

    protected:
    };
} // namespace Raytracer
