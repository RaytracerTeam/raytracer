/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialTexture.cpp
*/

#include "Scene/Materials/MaterialTexture.hpp"

#include <cmath>

namespace Raytracer {
    MaterialTexture::MaterialTexture(const std::string &pathname)
    {
        setTexture(pathname);
    }

    MaterialTexture::MaterialTexture(std::shared_ptr<sf::Image> image)
        : m_image(image)
    {
    }

    void MaterialTexture::setTexture(const std::string &pathname)
    {
        m_image = std::make_shared<sf::Image>();
        if (!m_image->loadFromFile(pathname))
            std::cerr << "Texture can't be loaded MaterialTexture::setTexture" << std::endl;
        m_pathname = pathname;
    }

    /* todo : implement */
    Color MaterialTexture::getColor(const RayHit &) const
    {
        return Color(1., 0, 1);
    }

    Color MaterialTexture::getColor(double u, double v) const
    {
        auto size = m_image->getSize();
        auto x = u * size.x;
        auto y = v * size.y;
        if (x < 0 || x >= size.x || y < 0 || y >= size.y)
            return Color(1., 0, 1);
        sf::Color color = m_image->getPixel(x, y);
        return Color((unsigned int)color.r, color.g, color.b);
    }
} // namespace Raytracer
