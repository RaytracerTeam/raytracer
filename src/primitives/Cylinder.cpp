/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cylinder.cpp
*/

#include "Primitives/Cylinder.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>

namespace Raytracer {

    static RayHit getNormal(double distance, const Math::Vector3D &hitPt, const Math::Vector3D &origin)
    {
        auto normal = Math::Vector3D(
            hitPt.getX() - origin.getX(),
            0,
            hitPt.getZ() - origin.getZ())
                          .normalize();

        return RayHit(distance, hitPt, normal);
    }

    RayHit Cylinder::hit(const Ray &ray)
    {
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;
        Math::Vector3D rayDir = ray.getDirection();

        // double a = std::pow(rayDir.getX(), 2.) * std::pow(rayDir.getZ(), 2.);
        // double b = 2 * (rayDir.getX() * dstOrigin.getX() + rayDir.getZ() * dstOrigin.getZ());
        // double c = std::pow(dstOrigin.getX(), 2.) * std::pow(dstOrigin.getZ(), 2.) - std::pow(m_radius, 2.);

        double a = (rayDir.getX() * rayDir.getX()) + (rayDir.getZ() * rayDir.getZ());
        double b = 2 * (rayDir.getX() * (rayDir.getX()) + rayDir.getZ() * (dstOrigin.getZ()));
        double c = (rayDir.getX()) * (rayDir.getX()) + (dstOrigin.getZ()) * (dstOrigin.getZ()) - (m_radius * m_radius);
        double delta = std::pow(b, 2.) - 4 * a * c;

        if (delta <= 0.001) // hit nothing
            return RayHit();

        double t0 = (-b - std::sqrt(delta)) / (2 * a);
        Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * t0;
        if (std::isinf(m_height))
            return getNormal(t0, hitPt, m_origin);

        if (hitPt.getY() >= m_origin.getY() && hitPt.getY() <= m_origin.getY() + m_height)
            return getNormal(t0, hitPt, m_origin);

        double t1 = (-b + std::sqrt(delta)) / (2 * a);
        hitPt = ray.getOrigin() + ray.getDirection() * t1;
        if ((hitPt.getY() >= m_origin.getY() && hitPt.getY() <= m_origin.getY() + m_height))
            return getNormal(t1, hitPt, m_origin);
        return RayHit();
    }
} // namespace Raytracer
