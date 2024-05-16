/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SphereTexture.hpp
*/

#pragma once

#include "Scene/Materials/MaterialTexture.hpp"

namespace Raytracer {
    class SphereTexture : public MaterialTexture {
    public:
        SphereTexture() = default;
        SphereTexture(const std::string &pathname) : MaterialTexture(pathname) {}
        SphereTexture(std::shared_ptr<sf::Image> image) : MaterialTexture(image) {}
        ~SphereTexture() = default;

        MaterialType getType() const override { return MaterialType::TEXTURE_SPHERE; }

        Color getColor(const RayHit &rayhit) const override final;
    };
} // namespace Raytracer
