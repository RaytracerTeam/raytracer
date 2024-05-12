/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** PlaneTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/PlaneTexture.hpp"

#include <cmath>

namespace Raytracer {
    Color PlaneTexture::getColor(const RayHit &ray) const
    {
        if (m_image.get() == nullptr)
            return Color(1., 0, 1);

        (void)ray;
        // auto d = ray.getHitPoint();
        float u = 2;
        float v = 2;

        return MaterialTexture::getColor(u, v);
    }
} // namespace Raytracer
