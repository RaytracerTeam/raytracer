/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cone.cpp
*/

#include "Scene/Primitives/Cone.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>

namespace Raytracer {

    BoundingBox Cone::getBoundingBox(void) const
    {
        return BoundingBox(
            Math::Vector3D(m_origin.getX() - m_radius, m_origin.getY(), m_origin.getZ() - m_radius),
            Math::Vector3D(m_origin.getX() + m_radius, m_origin.getY() + m_height, m_origin.getZ() + m_radius));
    }

    RayHit Cone::getNormal(double distance, const Math::Vector3D &hitPt, const Math::Vector3D &origin) const
    {
        double r = std::sqrt(std::pow(hitPt.getX() - origin.getX(), 2) + std::pow(hitPt.getZ() - origin.getZ(), 2));
        auto normal = Math::Vector3D(
            hitPt.getX() - origin.getX(),
            r * (m_radius / m_height),
            hitPt.getZ() - origin.getZ())
                          .normalize();

        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Cone::hit(const Ray &ray) const
    {
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;
        Math::Vector3D rayDir = ray.getDirection();

        double tan = (m_radius / m_height) * (m_radius / m_height);

        double a = rayDir.getX() * rayDir.getX() + rayDir.getZ() * rayDir.getZ() - tan * rayDir.getY() * rayDir.getY();
        double b = 2 * (rayDir.getX() * dstOrigin.getX() + rayDir.getZ() * dstOrigin.getZ() - tan * rayDir.getY() * dstOrigin.getY());
        double c = dstOrigin.getX() * dstOrigin.getX() + dstOrigin.getZ() * dstOrigin.getZ() - tan * dstOrigin.getY() * dstOrigin.getY();
        double delta = std::pow(b, 2.) - 4 * a * c;

        if (delta <= 0.001) // hit nothing
            return std::nullopt;

        double sqrtDelta = std::sqrt(delta);

        double t0 = (-b - sqrtDelta) / (2 * a);
        if (t0 > 0.001) {
            Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * t0;
            if (std::isinf(m_height))
                return getNormal(t0, hitPt, m_origin);

            if (hitPt.getY() >= m_origin.getY() && hitPt.getY() <= m_origin.getY() + m_height)
                return getNormal(t0, hitPt, m_origin);
        }

        double t1 = (-b + sqrtDelta) / (2 * a);
        if (t1 > 0.001) {
            Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * t1;
            if (hitPt.getY() >= m_origin.getY() && hitPt.getY() <= m_origin.getY() + m_height)
                return getNormal(t1, hitPt, m_origin);
        }
        return std::nullopt;
    }
} // namespace Raytracer
