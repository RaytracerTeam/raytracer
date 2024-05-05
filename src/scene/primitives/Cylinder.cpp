/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cylinder.cpp
*/

#include "Scene/Primitives/Cylinder.hpp"
#include "Math/Vector3D.hpp"
#include <cmath>

namespace Raytracer {
    RayHit Cylinder::getNormal(double distance, const Math::Vector3D &hitPt,
        const Math::Vector3D &origin) const
    {
        auto normal = Math::Vector3D(
            hitPt.getX() - origin.getX(), 0, hitPt.getZ() - origin.getZ())
                          .normalize();

        return RayHit(distance, hitPt, normal);
    }

    // std::optional<RayHit> Cylinder::hitFace(
    //     const Math::Vector3D &dstOrigin, const Math::Vector3D &rayDir) const
    // {
    //     std::optional<RayHit> intersect = std::nullopt;

    //     double t0 = -dstOrigin.getY() / rayDir.getY();

    //     Math::Vector3D hitPt0
    //         = Math::Vector3D(dstOrigin.getX() + rayDir.getX() * t0, 0,
    //             dstOrigin.getZ() + rayDir.getZ() * t0);

    //     if (t0 > 1e-8
    //         && hitPt0.getX() * hitPt0.getX() + hitPt0.getZ() * hitPt0.getZ()
    //             <= m_radius * m_radius) {
    //         auto normal = getNormal(t0, hitPt0, m_origin).getNormal();
    //         intersect = RayHit(t0, hitPt0, -normal);
    //     }

    //     double t1 = (m_height - dstOrigin.getY()) / rayDir.getY();

    //     Math::Vector3D hitPt1
    //         = Math::Vector3D(dstOrigin.getX() + rayDir.getX() * t1, m_height,
    //             dstOrigin.getZ() + rayDir.getZ() * t1);

    //     if (t1 > 1e-8 && (!intersect.has_value() || t1 < t0)
    //         && hitPt1.getX() * hitPt1.getX() + hitPt1.getZ() * hitPt1.getZ()
    //             <= m_radius * m_radius) {
    //         auto normal = getNormal(t1, hitPt1, m_origin).getNormal();
    //         intersect = RayHit(t1, hitPt1, -normal);
    //     }

    //     return intersect;
    // }

    std::optional<RayHit> Cylinder::hitFace(
        const Math::Vector3D &dstOrigin, const Math::Vector3D &rayDir) const
    {
        double t0 = -dstOrigin.getY() / rayDir.getY();
        double t1 = (m_height - dstOrigin.getY()) / rayDir.getY();

        double t = (t0 < t1 && t0 > 1e-8) ? t0 : t1;
        if (t < -1e-8)
            return std::nullopt;

        Math::Vector3D hitPt
            = Math::Vector3D(dstOrigin.getX() + rayDir.getX() * t, 0,
                dstOrigin.getZ() + rayDir.getZ() * t);
        (t0 < t1 && t0 > 1e-8) ? hitPt.setY(0) : hitPt.setY(m_height);

        if (hitPt.getX() * hitPt.getX() + hitPt.getZ() * hitPt.getZ()
            <= m_radius * m_radius) {
            // auto normal = getNormal(t, hitPt, m_origin).getNormal();
            // return RayHit(t, hitPt, -normal);
            auto normal = (t0 < t1 && t0 > 1e-8) ? Math::Vector3D(0, -1, 0)
                                                 : Math::Vector3D(0, 1, 0);
            return RayHit(t, hitPt, normal.normalize());
        }

        return std::nullopt;
    }

    std::optional<RayHit> Cylinder::hit(const Ray &ray) const
    {
        std::optional<RayHit> inter;
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;
        Math::Vector3D rayDir = ray.getDirection();

        double a
            = rayDir.getX() * rayDir.getX() + rayDir.getZ() * rayDir.getZ();
        double b = 2
            * (rayDir.getX() * dstOrigin.getX()
                + rayDir.getZ() * dstOrigin.getZ());
        double c = dstOrigin.getX() * dstOrigin.getX()
            + dstOrigin.getZ() * dstOrigin.getZ() - m_radius * m_radius;
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

        if ((inter = hitFace(dstOrigin, rayDir)).has_value())
            return inter.value();

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
