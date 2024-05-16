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
        Math::Vector3D minOrigin =
            Math::Algorithm::minOfVector3D(m_origin, m_transformations.getTranslation());
        Math::Vector3D maxOrigin =
            Math::Algorithm::maxOfVector3D(m_origin, m_transformations.getTranslation());

        double biggestScale = Math::Algorithm::maxOfThree(m_transformations.getScale().getX(),
            m_transformations.getScale().getY(), m_transformations.getScale().getZ());

        Math::Vector3D min = minOrigin - biggestScale * 3;
        Math::Vector3D max = maxOrigin + biggestScale * 3;

        return BoundingBox(min, max);
    }

    RayHit Tanglecube::getNormal(double distance, const Math::Vector3D &bckHitPt,
        const Math::Vector3D &origin) const
    {
        Math::Vector3D dstOrigin = bckHitPt - origin;

        auto bckNormal = Math::Vector3D(
            4. * std::pow(dstOrigin.getX(), 3) - 10. * dstOrigin.getX(),
            4. * std::pow(dstOrigin.getY(), 3) - 10. * dstOrigin.getY(),
            4. * std::pow(dstOrigin.getZ(), 3) - 10. * dstOrigin.getZ())
                          .normalize();

        Math::Vector3D hitPt = m_matrixT.applyForward(bckHitPt);
        Math::Vector3D normal = m_matrixT.applyForward(bckNormal);
        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Tanglecube::hit(const Ray &ray) const
    {
        Ray bckRay = m_matrixT.applyBackward(ray);

        Math::Vector3D dstOrigin = bckRay.getOrigin() - m_bckOrigin - m_bckTranslation;
        Math::Vector3D rayDir = bckRay.getDirection();

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
            + m_radius;

        // TODO remplacer par une std::array
        double roots[4] = { 0 };

        Math::Algorithm::solveQuarticEquation(a, b, c, d, e, roots);

        Math::Algorithm::sortRoots(roots, 4);

        for (int i = 0; i < 4; i++) {
            if (roots[i] > TOLERANCE) {
                Math::Vector3D bckHitPt = bckRay.getOrigin() + bckRay.getDirection() * roots[i];
                return getNormal(roots[i], bckHitPt, m_bckOrigin + m_bckTranslation);
            }
        }

        return std::nullopt;
    }
} // namespace Raytracer
