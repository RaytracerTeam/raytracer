/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cylinder.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Cylinder : public APrimitive {
    public:
        Cylinder(const Math::Vector3D &origin,  std::unique_ptr<IMaterial> material, double radius, double height)
            : APrimitive(origin, std::move(material))
            , m_radius(radius)
            , m_height(height) {}
        ~Cylinder() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::CYLINDER; };

        float getRadius() const { return m_radius; }
        float getHeight() const { return m_height; }

        void setRadius(float radius) { m_radius = radius; }
        void setHeight(float height) { m_height = height; }

        std::optional<RayHit> hit(const Ray &ray) const override;

    private:
        double m_radius;
        double m_height;
    };
} // namespace Raytracer
