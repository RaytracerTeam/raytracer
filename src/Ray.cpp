/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.cpp
*/

#include "Ray.hpp"

namespace Raytracer {
    Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
    {
        m_direction = direction.normalize();
        m_origin = origin;
    }
}
