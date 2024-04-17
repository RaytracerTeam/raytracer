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
        Sphere(double radius) : m_radius(radius) {};
        ~Sphere() = default;

        bool hit(const Ray &ray, RayHit &rayhit) override;
    private:
        double m_radius;
    };
} // namespace Raytracer
