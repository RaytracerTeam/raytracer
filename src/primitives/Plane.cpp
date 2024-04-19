/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Plane.cpp
*/

#include "Primitives/Plane.hpp"
#include "Math/Vector3D.hpp"

#include <cmath>

namespace Raytracer {
    Plane::Plane(double pos, const Axis &axis) : m_axis(axis)
    {
        auto inf = std::numeric_limits<double>::infinity();;
        switch (m_axis) {
            case X:
                setOrigin(Math::Vector3D(pos, inf, inf));
                break;
            case Y:
                setOrigin(Math::Vector3D(inf, pos, inf));
                break;
            default:
                setOrigin(Math::Vector3D(inf, inf, pos));
                break;
        }
    }

    static double calculateT(double rayOrigin, double origin, double rayDir)
    {
        return -(rayOrigin - origin) / rayDir;
    }

    RayHit Plane::hit(const Ray &ray)
    {
        double t;
        auto rayOrigin = ray.getOrigin();
        auto rayDir = ray.getDirection();

        switch (m_axis) {
            case X:
                t = calculateT(rayOrigin.getX(), m_origin.getX(), rayDir.getX());
                break;
            case Y:
                t = calculateT(rayOrigin.getY(), m_origin.getY(), rayDir.getY());
                break;
            default:
                t = calculateT(rayOrigin.getZ(), m_origin.getZ(), rayDir.getZ());
                break;
        }
        if (t <= 0 || std::isinf(t))
           return RayHit();
        return RayHit(t, (rayOrigin + rayDir * t), getNormal());
    }

    Math::Vector3D Plane::getNormal(void)
    {
        switch (m_axis) {
            case X:
                return Math::Vector3D(1, 0, 0);
            case Y:
                return Math::Vector3D(0, 1, 0);
            default:
                return Math::Vector3D(0, 0, 1);
        }
    }
} // namespace Raytracer