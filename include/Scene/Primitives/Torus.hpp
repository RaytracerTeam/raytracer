/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Torus.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Torus : public APrimitive {
    public:
        Torus(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material, double radius, double distance)
            : APrimitive(origin, std::move(material))
            , m_radius(radius)
            , m_distance(distance)
        {
        }
        ~Torus() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::TORUS; };
        const std::string getTypeString(void) const override { return "Torus"; };

        float getRadius() const { return m_radius; }
        float getDistance() const { return m_distance; }

        void setRadius(float radius) { m_radius = radius; }
        void setDistance(float distance) { m_distance = distance; }

        std::optional<RayHit> hit(const Ray &ray) const override;
        RayHit getNormal(double distance, const Math::Vector3D &hitPt, const Math::Vector3D &origin) const;

    private:
        double m_radius;
        double m_distance;
    };
} // namespace Raytracer
