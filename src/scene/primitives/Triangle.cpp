/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Triangle.cpp
*/

#include "Scene/Primitives/Triangle.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Algorithm.hpp"

namespace Raytracer {
    BoundingBox Triangle::getBoundingBox(void) const
    {
        Math::Vector3D min = Math::Vector3D(
            std::min(m_origin.getX(), std::min(m_v1.getX(), m_v2.getX())),
            std::min(m_origin.getY(), std::min(m_v1.getY(), m_v2.getY())),
            std::min(m_origin.getZ(), std::min(m_v1.getZ(), m_v2.getZ())));

        Math::Vector3D max = Math::Vector3D(
            std::max(m_origin.getX(), std::max(m_v1.getX(), m_v2.getX())),
            std::max(m_origin.getY(), std::max(m_v1.getY(), m_v2.getY())),
            std::max(m_origin.getZ(), std::max(m_v1.getZ(), m_v2.getZ())));

        double biggestScale = Math::Algorithm::maxOfThree(m_transformations.getScale().getX(),
            m_transformations.getScale().getY(), m_transformations.getScale().getZ());

        if (m_transformations.getRotation().getX() < TOLERANCE &&
        m_transformations.getRotation().getY() < TOLERANCE &&
        m_transformations.getRotation().getZ() < TOLERANCE) {
            min = m_transformations.getTranslation() + min * biggestScale;
            max = m_transformations.getTranslation() + max * biggestScale;
            return BoundingBox(min, max);
        }

        Math::Vector3D middle = Math::Vector3D((m_origin.getX() + m_v1.getX() + m_v2.getX()) / 3.,
        (m_origin.getY() + m_v1.getY() + m_v2.getY()) / 3., (m_origin.getZ() + m_v1.getZ() + m_v2.getZ()) / 3.);

        Math::Vector3D radius = max - min;
        min = m_transformations.getTranslation() + min - radius * biggestScale;
        max = m_transformations.getTranslation() + max + radius * biggestScale;

        return BoundingBox(min, max);
    }

    std::optional<RayHit> Triangle::hit(const Ray &ray) const
    {
        Ray bckRay = m_matrixT.applyBackward(ray);

        Math::Vector3D v0 = m_origin + m_bckTranslation;
        Math::Vector3D v1 = m_v1 + m_bckTranslation;
        Math::Vector3D v2 = m_v2 + m_bckTranslation;

        Math::Vector3D edge1 = v1 - v0;
        Math::Vector3D edge2 = v2 - v0;
        Math::Vector3D ray_cross_e2 = bckRay.getDirection().cross(edge2);
        float det = edge1.dot(ray_cross_e2);

        if (det > -TOLERANCE && det < TOLERANCE)
            return std::nullopt;

        float inv_det = 1.0 / det;
        Math::Vector3D s = bckRay.getOrigin() - v0;
        float u = inv_det * s.dot(ray_cross_e2);

        if (u < 0 || u > 1)
            return std::nullopt;

        Math::Vector3D s_cross_e1 = s.cross(edge1);
        float v = inv_det * bckRay.getDirection().dot(s_cross_e1);

        if (v < 0 || u + v > 1)
            return std::nullopt;

        float t = inv_det * edge2.dot(s_cross_e1);

        if (t > TOLERANCE) {
            Math::Vector3D bckHitPt = bckRay.getOrigin() + bckRay.getDirection() * t;
            Math::Vector3D bckNormal = edge1.cross(edge2).normalize();
            if (bckNormal.dot(bckRay.getDirection()) > 0)
                bckNormal = -bckNormal;

            Math::Vector3D hitPt = m_matrixT.applyForward(bckHitPt);
            Math::Vector3D normal = m_matrixT.applyForward(bckNormal);
            return RayHit(t, hitPt, normal, getBarycentricCoordinates(hitPt));
        }

        return std::nullopt;
    }

    Math::Vector3D Triangle::getBarycentricCoordinates(const Math::Vector3D &point) const
    {
        if (this->getMaterial()->getType() != MaterialType::TEXTURE_TRIANGLE)
            return Math::Vector3D(0, 0, 0);
        Math::Vector3D edge1 = m_v1 - m_origin;
        Math::Vector3D edge2 = m_v2 - m_origin;
        Math::Vector3D edge3 = point - m_origin;
        float d00 = edge1.dot(edge1);
        float d01 = edge1.dot(edge2);
        float d11 = edge2.dot(edge2);
        float d20 = edge3.dot(edge1);
        float d21 = edge3.dot(edge2);
        float denom = d00 * d11 - d01 * d01;
        float w0 = (d11 * d20 - d01 * d21) / denom;
        float w1 = (d00 * d21 - d01 * d20) / denom;
        float w2 = 1.0f - w0 - w1;
        return Math::Vector3D(w0, w1, w2);
    }
} // namespace Raytracer
