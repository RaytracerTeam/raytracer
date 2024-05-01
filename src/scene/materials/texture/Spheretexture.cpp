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

    /* todo : implement */
    Color SphereTexture::getColor(const RayHit &) const
    {
        return Color(255U, 0, 0);
    }

    Color SphereTexture::getColor(double u, double v) const
    {
        auto size = m_image->getSize();
        auto x = u * size.x;
        auto y = v * size.y;
        sf::Color color = m_image->getPixel(x, y);
        return Color((unsigned int)color.r, color.g, color.b);
    }
} // namespace Raytracer
