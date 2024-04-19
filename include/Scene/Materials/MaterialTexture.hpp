/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialTexture.hpp
*/

#pragma once

#include "IMaterial.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>

namespace Raytracer {
    class MaterialTexture : public IMaterial {
    public:
        MaterialTexture(const std::string &pathname);
        ~MaterialTexture() = default;

        Color getColor(const RayHit &rayhit) override;
    private:
        std::unique_ptr<sf::Texture> m_texture;
    };
} // namespace Raytracer
