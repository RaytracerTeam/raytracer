/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cylinder.cpp
*/

#include "Scene/Primitives/Cylinder.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Algorithm.hpp"
#include <cmath>

namespace Raytracer {
    BoundingBox Cylinder::getBoundingBox(void) const
    {
        Math::Vector3D newOrigin = m_origin + m_transformations.getTranslation();

        double biggestScale = Math::Algorithm::maxOfThree(m_transformations.getScale().getX(),
            m_transformations.getScale().getY(), m_transformations.getScale().getZ());

        Math::Vector3D min = newOrigin - biggestScale * (m_radius + m_height);
        Math::Vector3D max = newOrigin + biggestScale * (m_radius + m_height);

        return BoundingBox(min, max);
    }

    RayHit Cylinder::getNormal(double distance, const Math::Vector3D &bckHitPt, const Math::Vector3D &origin) const
    {
        auto bckNormal = Math::Vector3D(
            (bckHitPt.getX() - origin.getX()) / m_radius, 0, (bckHitPt.getZ() - origin.getZ()) / m_radius)
                          .normalize();

        Math::Vector3D hitPt = m_matrixT.applyForward(bckHitPt);
        Math::Vector3D normal = m_matrixT.applyForward(bckNormal);
        return RayHit(distance, hitPt, normal);
    }

    std::optional<RayHit> Cylinder::hitFace(
        const Math::Vector3D &dstOrigin, const Math::Vector3D &rayDir) const
    {
        double t0 = (-m_height - dstOrigin.getY()) / rayDir.getY();
        double t1 = (m_height - dstOrigin.getY()) / rayDir.getY();

        double t = (t0 < t1 && t0 > 1e-8) ? t0 : t1;
        if (t < -1e-8)
            return std::nullopt;

        Math::Vector3D bckHitPt
            = Math::Vector3D(dstOrigin.getX() + rayDir.getX() * t, 0,
                dstOrigin.getZ() + rayDir.getZ() * t);
        (t0 < t1 && t0 > 1e-8) ? bckHitPt.setY(-m_height) : bckHitPt.setY(m_height);

        if (bckHitPt.getX() * bckHitPt.getX() + bckHitPt.getZ() * bckHitPt.getZ()
            <= m_radius * m_radius) {
            // TODO fix normal with translation
            auto bckNormal = (t0 < t1 && t0 > 1e-8) ? Math::Vector3D(0, -1, 0).normalize()
                                                    : Math::Vector3D(0, 1, 0).normalize();

            Math::Vector3D hitPt = m_matrixT.applyForward(bckHitPt);
            Math::Vector3D normal = m_matrixT.applyForward(bckNormal);
            return RayHit(t, hitPt, normal);
        }

        return std::nullopt;
    }

    std::optional<RayHit> Cylinder::hit(const Ray &ray) const
    {
        Ray bckRay = m_matrixT.applyBackward(ray);
        Math::Vector3D newOrigin = m_bckOrigin + m_bckTranslation;

        std::optional<RayHit> intersect;
        Math::Vector3D dstOrigin = bckRay.getOrigin() - m_bckOrigin - m_bckTranslation;
        Math::Vector3D rayDir = bckRay.getDirection();

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
            Math::Vector3D bckHitPt = bckRay.getOrigin() + bckRay.getDirection() * t0;

            if (std::isinf(m_height))
                return getNormal(t0, bckHitPt, newOrigin);

            if (bckHitPt.getY() >= newOrigin.getY() - m_height &&
            bckHitPt.getY() <= newOrigin.getY() + m_height)
                return getNormal(t0, bckHitPt, newOrigin);
        }

        if ((intersect = hitFace(dstOrigin, rayDir)).has_value())
            return intersect.value();

        double t1 = (-b + sqrtDelta) / (2 * a);
        if (t1 > 0.001) {
            Math::Vector3D bckHitPt = bckRay.getOrigin() + bckRay.getDirection() * t1;

            if (bckHitPt.getY() >= newOrigin.getY() - m_height &&
            bckHitPt.getY() <= newOrigin.getY() + m_height)
                return getNormal(t1, bckHitPt, newOrigin);
        }

        return std::nullopt;
    }
} // namespace Raytracer
