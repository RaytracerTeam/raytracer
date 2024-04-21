/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Sphere.cpp
*/

#include "Scene/Primitives/Sphere.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>

namespace Raytracer {
    std::optional<RayHit> Sphere::hit(const Ray &ray) const
    {
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;
        Math::Vector3D rayDir = ray.getDirection();

        double a = rayDir.dot(rayDir);
        double b = 2 * rayDir.dot(dstOrigin);
        double c = dstOrigin.dot(dstOrigin) - std::pow(m_radius, 2.);
        double delta = std::pow(b, 2.) - 4 * a * c;

        if (delta <= 0.001) // hit nothing
            return std::nullopt;

        // doesn't care about 2nd result, need the nearest
        double distance = (-b - std::sqrt(delta)) / (2 * a);
        if (distance <= 0.001)
            return std::nullopt;

        Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * distance;
        return RayHit(distance, hitPt, (hitPt - m_origin).normalize());
    }
} // namespace Raytracer