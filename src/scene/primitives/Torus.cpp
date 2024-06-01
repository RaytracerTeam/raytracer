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
        Math::Vector3D newOrigin = m_origin + m_transformations.getTranslation();

        double biggestScale = Math::Algorithm::maxOfThree(m_transformations.getScale().getX(),
            m_transformations.getScale().getY(), m_transformations.getScale().getZ());

        Math::Vector3D min = newOrigin - biggestScale * (m_distance + m_radius);
        Math::Vector3D max = newOrigin + biggestScale * (m_distance + m_radius);

        return BoundingBox(min, max);
    }

    RayHit Torus::getNormal(double distance, const Math::Vector3D &bckHitPt,
        const Math::Vector3D &origin) const
    {
        Math::Vector3D u(bckHitPt.getX() - origin.getX(), bckHitPt.getY() - origin.getY(), 0.);
        u = u.normalize() * m_distance;
        u += origin;

        Math::Vector3D bckNormal = (bckHitPt - u).normalize();

        Math::Vector3D hitPt = m_matrixT.applyForward(bckHitPt);
        Math::Vector3D normal = m_matrixT.applyNormal(bckNormal);
        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Torus::hit(const Ray &ray) const
    {
        Ray bckRay = m_matrixT.applyBackward(ray);

        Math::Vector3D dstOrigin = bckRay.getOrigin() - m_bckOrigin - m_bckTranslation;
        Math::Vector3D rayDir = bckRay.getDirection();

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

        double roots[4] = { 0 };

        Math::Algorithm::solveQuarticEquation(j * j, 2. * j * k,
            2. * j * l + k * k - g, 2. * k * l - h, l * l - i, roots);

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
