/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** TriangleTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/TriangleTexture.hpp"

#include <cmath>

namespace Raytracer {
    Color TriangleTexture::getColor(const RayHit &ray) const
    {
        if (m_image.get() == nullptr)
            return Color(1., 0, 1);

        auto d = ray.getRelativeHitPoint();

        Math::Vector3D uv = m_vt1 * d.getX() + m_vt2 * d.getY() + m_vt3 * d.getZ();

        return MaterialTexture::getColor(uv.getX(), 1 - uv.getY());
    }
} // namespace Raytracer
