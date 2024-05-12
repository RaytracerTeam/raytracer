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

        return getColor(u, v);
    }

    Color TriangleTexture::getColor(double u, double v) const
    {
        auto size = m_image->getSize();
        auto x = u * size.x;
        auto y = (1 - v) * size.y;
        if (x < 0 || x >= size.x || y < 0 || y >= size.y)
            return Color(1., 0, 1);
        sf::Color color = m_image->getPixel(x, y);
        return Color((unsigned int)color.r, color.g, color.b);
    }
} // namespace Raytracer
