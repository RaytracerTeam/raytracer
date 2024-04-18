/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.cpp
*/

#include "Primitives/APrimitive.hpp"

namespace Raytracer {
    void APrimitive::setSolidColor(const Color &c)
    {
        m_texture.reset();
        m_color = c;
        m_textureType = SOLID;
    }

    void APrimitive::setCodeColor(Color (*colorCode)(const RayHit &))
    {
        m_texture.reset();
        m_colorCode = colorCode;
        m_textureType = CODE;
    }

    void APrimitive::setTexture(const std::string &pathname)
    {
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
        sf::Image image;

        if (image.loadFromFile(pathname))
            throw Error("Texture can't be loaded", "APrimitive::setTexture");

        texture->loadFromImage(image);
        m_texture = std::move(texture);
        m_textureType = TEXTURE;
    }

    ////////////

    // texture is based on UV mapping on primitive
    Color APrimitive::getColor(const RayHit &rayhit)
    {
        switch (m_textureType) {
        case SOLID:
            return m_color;
        case CODE:
            return m_colorCode(rayhit);
        default:
            return Color();
        }
    }
} // namespace Raytracer
