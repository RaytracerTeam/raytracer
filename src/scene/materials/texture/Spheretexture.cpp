/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SphereTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"

#include <cmath>

namespace Raytracer {
    Color SphereTexture::getColor(const RayHit &ray) const
    {
        if (m_image.get() == nullptr)
            return Color(1., 0, 1);

        auto d = ray.getRelativeHitPoint();
        float u = (0.5 + std::atan2(d.getZ(), d.getX()) / (2 * M_PI));
        float v = (0.5 - std::asin(d.getY()) / M_PI);

        return MaterialTexture::getColor(u, v);
    }
} // namespace Raytracer
