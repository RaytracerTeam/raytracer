/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Light.cpp
*/

#include "Light.hpp"

namespace Raytracer {
    Light::Light(const Math::Vector3D &origin, const Color &color)
        : m_origin(origin)
        , m_color(color)
    {
    }
}
