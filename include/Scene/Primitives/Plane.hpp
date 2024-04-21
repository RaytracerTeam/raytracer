/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Plane.hpp
*/

#pragma once

#include "APrimitive.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Plane : public APrimitive {
    public:
        enum Axis {
            X,
            Y,
            Z
        };
        Plane(const Math::Vector3D &origin,  std::unique_ptr<IMaterial> material) : APrimitive(origin, std::move(material)) {}
        Plane(double pos,  std::unique_ptr<IMaterial> material, const Axis &axis);
        ~Plane() = default;

        std::optional<RayHit> hit(const Ray &ray) const override;

        void setAxis(const Axis &axis) { m_axis = axis; }

    private:
        Math::Vector3D getNormal(void) const;
        Axis m_axis = Z;
    };
} // namespace Raytracer
