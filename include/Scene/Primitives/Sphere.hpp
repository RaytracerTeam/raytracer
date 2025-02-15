/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Sphere.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Sphere : public APrimitive {
    public:
        Sphere(const Math::Vector3D &origin,  std::unique_ptr<IMaterial> material,
            const Transformations &transformations, double radius)
            : APrimitive(origin, std::move(material), transformations)
            , m_radius(radius)
        {
        }
        ~Sphere() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::SPHERE; };

        double getRadius(void) const { return m_radius; }
        void setRadius(double radius) { m_radius = radius; }

        BoundingBox getBoundingBox(void) const override;
        std::optional<RayHit> hit(const Ray &ray) const override;

    private:
        double m_radius;
    };
} // namespace Raytracer
