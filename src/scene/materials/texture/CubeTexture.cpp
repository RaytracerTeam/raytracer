/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** CubeTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/CubeTexture.hpp"

#include <cmath>

namespace Raytracer {
    Color CubeTexture::getColor(const RayHit &ray) const
    {
        if (m_image.get() == nullptr)
            return Color(1., 0, 1);

        auto d = ray.getRelativeHitPoint();
        float threshold = 0.00001;
        float u;
        float v;
        if (d.getY() < threshold || d.getY() > 1 - threshold) {
            u = d.getX();
            v = d.getZ();
        } else if (d.getX() < threshold || d.getX() > 1 - threshold) {
            u = d.getZ();
            v = 1 - d.getY();
        } else if (d.getZ() < threshold || d.getZ() > 1 - threshold) {
            u = d.getX();
            v = 1 - d.getY();
        } else {
            u = d.getX();
            v = 1 - d.getZ();
        }

        return MaterialTexture::getColor(u, v);
    }
} // namespace Raytracer
