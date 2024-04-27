/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cone.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Cone : public APrimitive {
    public:
        Cone(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material, double radius, double height)
            : APrimitive(origin, std::move(material))
            , m_radius(radius)
            , m_height(height)
        {
        }
        ~Cone() = default;

        std::optional<RayHit> hit(const Ray &ray) const override;
        RayHit getNormal(double distance, const Math::Vector3D &hitPt, const Math::Vector3D &origin) const;

    private:
        double m_radius;
        double m_height;
    };
} // namespace Raytracer
