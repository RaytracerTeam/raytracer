/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Light.hpp
*/

#pragma once

#include "Color.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Light {
    public:
        Light() = default;
        Light(const Math::Vector3D &origin, const Color &color);
        ~Light() = default;

        Math::Vector3D getOrigin(void) const { return m_origin; }
        Color getColor(void) const { return m_color; }
        void setOrigin(const Math::Vector3D &origin) { m_origin = origin; }
        void setColor(const Color &color) { m_color = color; }

    private:
        Math::Vector3D m_origin;
        Color m_color;
    };
} // namespace Raytracer
