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
        Sphere(const Math::Vector3D &origin,  std::unique_ptr<IMaterial> material, double radius)
            : APrimitive(origin, std::move(material))
            , m_radius(radius)
        {
        }
        ~Sphere() = default;

        std::optional<RayHit> hit(const Ray &ray) const override;

    private:
        double m_radius;
    };
} // namespace Raytracer
