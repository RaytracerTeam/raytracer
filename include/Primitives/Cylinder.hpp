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
        Cylinder(double radius, double height)
            : m_radius(radius)
            , m_height(height) {};
        ~Cylinder() = default;

        RayHit hit(const Ray &ray) override;

    private:
        double m_radius;
        double m_height;
    };
} // namespace Raytracer
