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
    #define DEFAULT_POINTLIGHT_RADIUS 0.5f
    #define DEFAULT_POINTLIGHT_INTENSITY 1.0f

    class PointLight : public AShapeLight {
    public:
        PointLight(const Math::Vector3D &origin, double radius, const Color &color, double intensity);
        ~PointLight() = default;

        LightType getType(void) const override { return LightType::POINT; }

        double getRadius(void) const { return m_sphere.getRadius(); }
        void setRadius(double radius) { m_sphere.setRadius(radius); }

        void setOrigin(const Math::Vector3D &origin) override;

        std::optional<RayHit> hit(const Ray &ray) const override;

    protected:
        Sphere m_sphere;
    };
} // namespace Raytracer
