/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Tanglecube.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Tanglecube : public APrimitive {
    public:
        Tanglecube(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material)
            : APrimitive(origin, std::move(material))
        {
        }
        ~Tanglecube() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::TANGLECUBE; };

        std::optional<RayHit> hit(const Ray &ray) const override;
        RayHit getNormal(double distance, const Math::Vector3D &hitPt, const Math::Vector3D &origin) const;
    };
} // namespace Raytracer
