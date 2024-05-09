/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialTexture.hpp
*/

#pragma once

#include "AMaterial.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/Image.hpp>

namespace Raytracer {
    class MaterialTexture : public AMaterial {
    public:
        MaterialTexture(const std::string &pathname);

        MaterialType getType() const override { return MaterialType::TEXTURE; }

        virtual Color getColor(const RayHit &rayhit) const override;
        virtual Color getColor(double u, double v) const;
        const std::string &getTexture(void) const { return m_pathname; }
        const std::string &getPathname(void) const { return m_pathname; }

        void setTexture(const std::string &pathname);
    protected:
        std::unique_ptr<sf::Image> m_image;
        std::string m_pathname;
    };
} // namespace Raytracer
