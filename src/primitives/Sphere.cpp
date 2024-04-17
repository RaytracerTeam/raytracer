/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Sphere.cpp
*/

#include "Primitives/Sphere.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>

namespace Raytracer {
    bool Sphere::hit(Ray &ray)
    {
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;

        double a = 1; // unit vector ?, what is it doing here
        double b = 2 * Math::Vector3D::gDot(dstOrigin, ray.getDirection());
        double c = dstOrigin.dot(dstOrigin) - std::pow(m_radius, 2.);
        double delta = std::pow(b, 2.) - 4 * a * c;

        if (delta >= 0) { // doesn't care about 2nd result, need the nearest
            double distance = (-b - std::sqrt(delta)) / 2 * a;
            if (distance >= 0) {
                // Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * distance;
                // RayHit(true, distance, hitPt, (hitPt - m_origin).normalize());
                return true;
            }
        }
        return false;
    }
} // namespace Raytracer
