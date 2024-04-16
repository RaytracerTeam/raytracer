/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Ray {
    public:
        Ray(Math::Vector3D &origin, Math::Vector3D &direction);
        ~Ray() = default;

        Math::Vector3D getOrigin(void) const { return m_origin; }
        Math::Vector3D getDirection(void) const { return m_direction; }
    private:
        Math::Vector3D m_origin = Math::Vector3D(0., 0., 0.);
        Math::Vector3D m_direction = Math::Vector3D(0., 0., 0.);
    };
} // namespace Raytracer
