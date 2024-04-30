/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** PointLight.cpp
*/

#include "Scene/Lights/PointLight.hpp"
#include "Scene/Materials/AMaterial.hpp"

namespace Raytracer {
        PointLight::PointLight(const Math::Vector3D &origin, double radius, const Color &color = { 255, 255, 255. }, double intensity = 1.)
            : AShapeLight(origin, color, intensity)
            , m_sphere(origin, nullptr, radius)
        {
        }

        std::optional<RayHit> PointLight::hit(const Ray &ray) const
        {
            return m_sphere.hit(ray);
        }
} // namespace Raytracer
