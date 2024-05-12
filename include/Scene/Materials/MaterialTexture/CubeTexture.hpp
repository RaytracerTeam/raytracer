/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** CubeTexture.hpp
*/

#pragma once

#include "Scene/Materials/MaterialTexture.hpp"

namespace Raytracer {
    class CubeTexture : public MaterialTexture {
    public:
        CubeTexture() = default;
        CubeTexture(const std::string &pathname, float factor = 1) : MaterialTexture(pathname) {}
        CubeTexture(std::shared_ptr<sf::Image> image, float factor = 1) : MaterialTexture(image) {}
        ~CubeTexture() = default;

        MaterialType getType() const override { return MaterialType::TEXTURE_CUBE; }

        Color getColor(const RayHit &rayhit) const override final;
    private:
    };
} // namespace Raytracer
