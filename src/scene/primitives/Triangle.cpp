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
    std::optional<RayHit> Triangle::hit(const Ray &ray) const
    {
        Math::Vector3D edge1 = m_v1 - m_v0;
        Math::Vector3D edge2 = m_v2 - m_v0;
        Math::Vector3D ray_cross_e2 = ray.getDirection().cross(edge2);
        float det = edge1.dot(ray_cross_e2);

        if (det > -TOLERANCE && det < TOLERANCE)
            return std::nullopt;

        float inv_det = 1.0 / det;
        Math::Vector3D s = ray.getOrigin() - m_v0;
        float u = inv_det * s.dot(ray_cross_e2);

        if (u < 0 || u > 1)
            return std::nullopt;

        Math::Vector3D s_cross_e1 = s.cross(edge1);
        float v = inv_det * ray.getDirection().dot(s_cross_e1);

        if (v < 0 || u + v > 1)
            return std::nullopt;

        float t = inv_det * edge2.dot(s_cross_e1);

        if (t > TOLERANCE) {
            Math::Vector3D hit = ray.getOrigin() + ray.getDirection() * t;
            Math::Vector3D normal = edge1.cross(edge2);
            if (normal.dot(ray.getDirection()) > 0)
                normal = -normal;
            return RayHit(t, hit, normal.normalize());
        }

        return std::nullopt;
    }
} // namespace Raytracer