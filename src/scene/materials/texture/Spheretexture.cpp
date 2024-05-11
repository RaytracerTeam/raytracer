/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SphereTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"

#include <cmath>

namespace Raytracer {
    SphereTexture::SphereTexture(const std::string &pathname) : MaterialTexture(pathname)
    {
    }

    Color SphereTexture::getColor(const RayHit &ray) const
    {
        if (!m_hasImage)
            return Color(1., 0, 1);

        auto d = ray.getRelativeHitPoint();
        float u = (0.5 + std::atan2(d.getZ(), d.getX()) / (2 * M_PI));
        float v = (0.5 - std::asin(d.getY()) / M_PI);

        return getColor(u, v);
    }

    Color SphereTexture::getColor(double u, double v) const
    {
        // return Color((double)v, (double)u, u + v);
        auto size = m_image.getSize();
        auto x = u * size.x;
        auto y = v * size.y;
        if (x < 0 || x >= size.x || y < 0 || y >= size.y)
            return Color(1., 0, 1);
        sf::Color color = m_image.getPixel(x, y);
        return Color((unsigned int)color.r, color.g, color.b);
    }
} // namespace Raytracer
