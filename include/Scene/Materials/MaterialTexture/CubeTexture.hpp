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
        CubeTexture(const std::string &pathname) : MaterialTexture(pathname) {}
        CubeTexture(std::shared_ptr<sf::Image> image) : MaterialTexture(image) {}
        ~CubeTexture() = default;

        MaterialType getType() const override { return MaterialType::TEXTURE_CUBE; }

        Color getColor(const RayHit &rayhit) const override final;
    private:
    };
} // namespace Raytracer
