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
    RayHit Cone::getNormal(double distance, const Math::Vector3D &hitPt,
        const Math::Vector3D &origin) const
    {
        double r = std::sqrt(std::pow(hitPt.getX() - origin.getX(), 2)
            + std::pow(hitPt.getZ() - origin.getZ(), 2));
        auto normal = Math::Vector3D(hitPt.getX() - origin.getX(),
            r * (m_radius / m_height), hitPt.getZ() - origin.getZ())
                          .normalize();

        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Cone::hitFace(
        const Math::Vector3D &dstOrigin, const Math::Vector3D &rayDir) const
    {
        double t = (m_height - dstOrigin.getY()) / rayDir.getY();
        if (t < -1e-8)
            return std::nullopt;

        Math::Vector3D hitPt
            = Math::Vector3D(dstOrigin.getX() + rayDir.getX() * t, m_height,
                dstOrigin.getZ() + rayDir.getZ() * t);

        if (hitPt.getX() * hitPt.getX() + hitPt.getZ() * hitPt.getZ()
            <= m_radius * m_radius) {
            // auto normal = getNormal(t, hitPt, m_origin).getNormal();
            // return RayHit(t, hitPt, -normal);
            auto normal = Math::Vector3D(0, 1, 0);
            return RayHit(t, hitPt, normal.normalize());
        }

        return std::nullopt;
    }

    std::optional<RayHit> Cone::hit(const Ray &ray) const
    {
        std::optional<RayHit> intersect;
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;
        Math::Vector3D rayDir = ray.getDirection();

        double tan = (m_radius / m_height) * (m_radius / m_height);

        double a = rayDir.getX() * rayDir.getX() + rayDir.getZ() * rayDir.getZ()
            - tan * rayDir.getY() * rayDir.getY();
        double b = 2
            * (rayDir.getX() * dstOrigin.getX()
                + rayDir.getZ() * dstOrigin.getZ()
                - tan * rayDir.getY() * dstOrigin.getY());
        double c = dstOrigin.getX() * dstOrigin.getX()
            + dstOrigin.getZ() * dstOrigin.getZ()
            - tan * dstOrigin.getY() * dstOrigin.getY();
        double delta = std::pow(b, 2.) - 4 * a * c;

        double sqrtDelta = std::sqrt(delta);

        double t0 = (-b - sqrtDelta) / (2 * a);
        if (t0 > 0.001) {
            Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * t0;
            if (std::isinf(m_height))
                return getNormal(t0, hitPt, m_origin);

            if (hitPt.getY() >= m_origin.getY()
                && hitPt.getY() <= m_origin.getY() + m_height)
                return getNormal(t0, hitPt, m_origin);
        }

        if ((intersect = hitFace(dstOrigin, rayDir)).has_value())
            return intersect;

        double t1 = (-b + sqrtDelta) / (2 * a);
        if (t1 > 0.001) {
            Math::Vector3D hitPt = ray.getOrigin() + ray.getDirection() * t1;
            if (hitPt.getY() >= m_origin.getY()
                && hitPt.getY() <= m_origin.getY() + m_height)
                return getNormal(t1, hitPt, m_origin);
        }
        return std::nullopt;
    }
} // namespace Raytracer
