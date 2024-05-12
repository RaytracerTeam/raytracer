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
        // std::cout << "d: " << d.getX() << " " << d.getY() << " " << d.getZ() << std::endl;
        float u = d.dot(m_vt2 - m_vt1) / (m_vt2 - m_vt1).length();
        float v = d.dot(m_vt3 - m_vt1) / (m_vt3 - m_vt1).length();

        return MaterialTexture::getColor(u, 1 - v);
    }
} // namespace Raytracer
