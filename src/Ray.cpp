/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.cpp
*/

#include "Ray.hpp"

namespace Raytracer {
    Ray::Ray(Math::Vector3D &origin, Math::Vector3D &direction)
    {
        double length = direction.length();

        m_direction = direction / length;
        m_origin = origin;
    }
}
