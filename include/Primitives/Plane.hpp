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
        Plane() = default;
        Plane(double pos, const Axis &axis);
        ~Plane() = default;

        RayHit hit(const Ray &ray) override;

        void setAxis(const Axis &axis) { m_axis = axis; }
    private:
        Math::Vector3D getNormal(void);
        Axis m_axis = Z;
    };
} // namespace Raytracer
