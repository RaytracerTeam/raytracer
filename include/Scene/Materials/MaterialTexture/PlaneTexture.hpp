/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** PlaneTexture.hpp
*/

#pragma once

#include "Scene/Materials/MaterialTexture.hpp"

namespace Raytracer {
    class PlaneTexture : public MaterialTexture {
    public:
        PlaneTexture() = default;
        PlaneTexture(const std::string &pathname, float factor = 1) : MaterialTexture(pathname), m_factor(factor) {}
        PlaneTexture(std::shared_ptr<sf::Image> image, float factor = 1) : MaterialTexture(image), m_factor(factor) {}
        ~PlaneTexture() = default;

        MaterialType getType() const override { return MaterialType::TEXTURE_PLANE; }

        float getFactor() const { return m_factor; }
        void setFactor(float factor) { m_factor = factor; }

        Color getColor(const RayHit &rayhit) const override final;
    private:
        float m_factor;
    };
} // namespace Raytracer
