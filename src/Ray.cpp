/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.cpp
*/

#include "Ray.hpp"

namespace Raytracer {
    Ray::Ray(const Math::Vector3D &origin, const Math::Vector3D &direction)
    : m_origin(origin)
    , m_direction(direction)
    {
    }

    ////////////////////////////////////////:

    RayHit::RayHit(double distance, Math::Vector3D hitPt, Math::Vector3D normal)
        : m_hit(true)
        , m_distance(distance)
        , m_hitPt(hitPt)
        , m_normal(normal)
    {
    }

    RayHit::RayHit(const RayHit &rhit)
        : m_hit(rhit.m_hit)
        , m_distance(rhit.m_distance)
        , m_hitPt(rhit.m_hitPt)
        , m_normal(rhit.m_normal)
    {
    }

    RayHit &RayHit::operator=(const RayHit &rhit)
    {
        m_hit = rhit.m_hit;
        m_distance = rhit.m_distance;
        m_hitPt = rhit.m_hitPt;
        m_normal = rhit.m_normal;
        return *this;
    }
}
