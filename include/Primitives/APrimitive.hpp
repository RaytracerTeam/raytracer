/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.h
*/

#pragma once

#include <memory>

#include "IPrimitive.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace Raytracer {
    class APrimitive : public IPrimitive {

        enum MaterialType {
            SOLID,
            CODE, // algorithm
            TEXTURE
        };
        public:
            virtual void setOrigin(const Math::Vector3D &v) override {
                m_origin = v;
            }
            virtual void setAngle(const Math::Angle3D &a) override {
                m_angle = a;
            }

            void setSolidColor(const Color &c) override;
            void setCodeColor(Color (*colorCode)(const RayHit &));
            void setTexture(const std::string &pathname);

            virtual Color getColor(const RayHit &rayhit) override;
        protected:
            APrimitive() = default;
            ~APrimitive() = default;

            Math::Angle3D m_angle;
            Math::Vector3D m_origin;

            // Material
            MaterialType m_textureType = SOLID;
            Color m_color;
            Color (*m_colorCode)(const RayHit &);
            std::unique_ptr<sf::Texture> m_texture;

    };
} // namespace Raytracer
