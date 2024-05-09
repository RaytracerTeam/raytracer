/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Torus.cpp
*/

#include "Scene/Primitives/Torus.hpp"
#include "Math/Algorithm.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    BoundingBox Torus::getBoundingBox(void) const
    {
        return BoundingBox(Math::Vector3D(m_origin - m_distance - m_radius),
            Math::Vector3D(m_origin + m_distance + m_radius));
    }

    RayHit Torus::getNormal(double distance, const Math::Vector3D &hitPt,
        const Math::Vector3D &origin) const
    {
        Math::Vector3D dstOrigin = hitPt - origin;

        double a = 1.
            - (m_distance
                / std::sqrt(dstOrigin.getX() * dstOrigin.getX()
                    + dstOrigin.getY() * dstOrigin.getY()));

        auto normal = Math::Vector3D(
            a * dstOrigin.getX(), a * dstOrigin.getY(), dstOrigin.getZ())
                          .normalize();

        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Torus::hit(const Ray &ray) const
    {
        Math::Vector3D dstOrigin = ray.getOrigin() - m_origin;
        Math::Vector3D rayDir = ray.getDirection();

        double g = 4. * m_distance * m_distance
            * (rayDir.getX() * rayDir.getX() + rayDir.getY() * rayDir.getY());

        double h = 8. * m_distance * m_distance
            * (dstOrigin.getX() * rayDir.getX()
                + dstOrigin.getY() * rayDir.getY());

        double i = 4. * m_distance * m_distance
            * (dstOrigin.getX() * dstOrigin.getX()
                + dstOrigin.getY() * dstOrigin.getY());

        double j = rayDir.getX() * rayDir.getX() + rayDir.getY() * rayDir.getY()
            + rayDir.getZ() * rayDir.getZ();

        double k = 2.
            * (dstOrigin.getX() * rayDir.getX()
                + dstOrigin.getY() * rayDir.getY()
                + dstOrigin.getZ() * rayDir.getZ());

        double l = dstOrigin.getX() * dstOrigin.getX()
            + dstOrigin.getY() * dstOrigin.getY()
            + dstOrigin.getZ() * dstOrigin.getZ() + m_distance * m_distance
            - m_radius * m_radius;

        // TODO remplacer par une std::array
        double roots[4] = { 0 };

        Math::Algorithm::solveQuarticEquation(j * j, 2. * j * k,
            2. * j * l + k * k - g, 2. * k * l - h, l * l - i, roots);

        Math::Algorithm::sortRoots(roots, 4);

        for (int i = 0; i < 4; i++) {
            if (roots[i] > TOLERANCE) {
                Math::Vector3D hitPt
                    = ray.getOrigin() + ray.getDirection() * roots[i];
                return getNormal(roots[i], hitPt, m_origin);
            }
        }
        return std::nullopt;
    }
} // namespace Raytracer
