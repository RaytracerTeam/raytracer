/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** PlaneTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/PlaneTexture.hpp"

#include <cmath>

namespace Raytracer {
    Color PlaneTexture::getColor(const RayHit &ray) const
    {
        if (m_image.get() == nullptr)
            return Color(1., 0, 1);

        auto d = ray.getHitPoint();

        float u = std::fmod(std::abs(d.getX()), m_factor) / m_factor;
        float v = std::fmod(std::abs(d.getZ()), m_factor) / m_factor;

        return MaterialTexture::getColor(u, v);
    }
} // namespace Raytracer
