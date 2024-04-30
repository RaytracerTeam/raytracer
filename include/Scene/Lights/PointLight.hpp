/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** PointLight.hpp
*/

#pragma once

#include "AShapeLight.hpp"
#include "Scene/Primitives/Sphere.hpp"

namespace Raytracer {
    class PointLight : public AShapeLight {
    public:
        PointLight(const Math::Vector3D &origin, double radius, const Color &color, double intensity);
        ~PointLight() = default;

        std::optional<RayHit> hit(const Ray &ray) const override;

    protected:
        Sphere m_sphere;
    };
} // namespace Raytracer
