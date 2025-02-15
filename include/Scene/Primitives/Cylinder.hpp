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
        Cylinder(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material,
            const Transformations &transformations, double radius, double height)
            : APrimitive(origin, std::move(material), transformations)
            , m_radius(radius)
            , m_height(height)
        {
        }
        ~Cylinder() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::CYLINDER; };

        float getRadius() const { return m_radius; }
        float getHeight() const { return m_height; }

        void setRadius(float radius) { m_radius = radius; }
        void setHeight(float height) { m_height = height; }

        BoundingBox getBoundingBox(void) const override;
        std::optional<RayHit> hit(const Ray &ray) const override;
        std::optional<RayHit> hitFace(const Math::Vector3D &dstOrigin, const Math::Vector3D &rayDir) const;
        RayHit getNormal(double distance, const Math::Vector3D &bckHitPt, const Math::Vector3D &origin) const;

    private:
        double m_radius;
        double m_height;
    };
} // namespace Raytracer
