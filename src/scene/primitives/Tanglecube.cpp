/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Tanglecube.cpp
*/

#include "Scene/Primitives/Tanglecube.hpp"
#include "Math/Algorithm.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    BoundingBox Tanglecube::getBoundingBox(void) const
    {
        return BoundingBox(
            Math::Vector3D(m_origin - 3.), Math::Vector3D(m_origin + 3.));
    }

    RayHit Tanglecube::getNormal(double distance, const Math::Vector3D &hitPt,
        const Math::Vector3D &origin) const
    {
        Math::Vector3D dstOrigin = hitPt - origin;

        auto normal = Math::Vector3D(
            4. * std::pow(dstOrigin.getX(), 3) - 10. * dstOrigin.getX(),
            4. * std::pow(dstOrigin.getY(), 3) - 10. * dstOrigin.getY(),
            4. * std::pow(dstOrigin.getZ(), 3) - 10. * dstOrigin.getZ())
                          .normalize();
        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Tanglecube::hit(const Ray &ray) const
    {
        Math::Vector3D dstOrigin = getTMatrix() * (ray.getOrigin() - m_origin);
        Math::Vector3D rayDir = getTMatrix() * ray.getDirection();

        double a = std::pow(rayDir.getX(), 4) + std::pow(rayDir.getY(), 4)
            + std::pow(rayDir.getZ(), 4);

        double b = 4.
            * (dstOrigin.getX() * std::pow(rayDir.getX(), 3)
                + dstOrigin.getY() * std::pow(rayDir.getY(), 3)
                + dstOrigin.getZ() * std::pow(rayDir.getZ(), 3));

        double c = 6.
                * (std::pow(dstOrigin.getX(), 2) * std::pow(rayDir.getX(), 2)
                    + std::pow(dstOrigin.getY(), 2) * std::pow(rayDir.getY(), 2)
                    + std::pow(dstOrigin.getZ(), 2)
                        * std::pow(rayDir.getZ(), 2))
            - 5.
                * (std::pow(rayDir.getX(), 2) + std::pow(rayDir.getY(), 2)
                    + std::pow(rayDir.getZ(), 2));

        double d = 4.
                * (std::pow(dstOrigin.getX(), 3) * rayDir.getX()
                    + std::pow(dstOrigin.getY(), 3) * rayDir.getY()
                    + std::pow(dstOrigin.getZ(), 3) * rayDir.getZ())
            - 10.
                * (dstOrigin.getX() * rayDir.getX()
                    + dstOrigin.getY() * rayDir.getY()
                    + dstOrigin.getZ() * rayDir.getZ());

        double e = std::pow(dstOrigin.getX(), 4) + std::pow(dstOrigin.getY(), 4)
            + std::pow(dstOrigin.getZ(), 4)
            - 5.
                * (std::pow(dstOrigin.getX(), 2) + std::pow(dstOrigin.getY(), 2)
                    + std::pow(dstOrigin.getZ(), 2))
            + 11.8;

        // TODO remplacer par une std::array
        double roots[4] = { 0 };

        Math::Algorithm::solveQuarticEquation(a, b, c, d, e, roots);

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
