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
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
        sf::Image image;

        if (image.loadFromFile(pathname))
            throw Error("Texture can't be loaded", "APrimitive::setTexture");

        texture->loadFromImage(image);
        m_texture = std::move(texture);
    }

    /* todo : implement */
    Color MaterialTexture::getColor(const RayHit &) const
    {
        return Color(255U, 0, 0);
    }
} // namespace Raytracer
