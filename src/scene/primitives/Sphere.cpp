/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Sphere.cpp
*/

#include "Scene/Primitives/Sphere.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Algorithm.hpp"
#include <cmath>

namespace Raytracer {
    BoundingBox Sphere::getBoundingBox(void) const
    {
        Math::Vector3D minOrigin =
            Math::Algorithm::minOfVector3D(m_origin, m_transformations.getTranslation());
        Math::Vector3D maxOrigin =
            Math::Algorithm::maxOfVector3D(m_origin, m_transformations.getTranslation());

        double biggestScale = Math::Algorithm::maxOfThree(m_transformations.getScale().getX(),
            m_transformations.getScale().getY(), m_transformations.getScale().getZ());

        Math::Vector3D min = minOrigin * 2 - biggestScale * m_radius;
        Math::Vector3D max = maxOrigin * 2 + biggestScale * m_radius;

        return BoundingBox(min, max);
    }

    std::optional<RayHit> Sphere::hit(const Ray &ray) const
    {
        Ray bckRay = m_matrixT.applyBackward(ray);

        Math::Vector3D dstOrigin = bckRay.getOrigin() - m_bckOrigin - m_bckTranslation;
        Math::Vector3D rayDir = bckRay.getDirection();

        double a = rayDir.dot(rayDir);
        double b = 2 * rayDir.dot(dstOrigin);
        double c = dstOrigin.dot(dstOrigin) - std::pow(m_radius, 2.);
        double delta = std::pow(b, 2.) - 4 * a * c;

        if (delta < -1e-8) // hit nothing
            return std::nullopt;

        // doesn't care about 2nd result, need the nearest
        double distance = (-b - std::sqrt(delta)) / (2 * a);
        if (distance < -1e-8)
            return std::nullopt;

        Math::Vector3D bckHitPt = bckRay.getOrigin() + bckRay.getDirection() * distance;
        Math::Vector3D hitPt = m_matrixT.applyForward(bckHitPt);

        return RayHit(distance, hitPt, (hitPt - m_fwdOrigin - m_fwdTranslation).normalize(),
            (hitPt - m_fwdOrigin - m_fwdTranslation) / m_radius);
    }
} // namespace Raytracer
