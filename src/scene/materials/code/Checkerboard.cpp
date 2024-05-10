/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Checkerboard.cpp
*/

#include "Scene/Materials/MaterialCode/Checkerboard.hpp"

#include <cmath>

namespace Raytracer {
    MaterialCheckerBoard::MaterialCheckerBoard(Color c1, Color c2, float factor)
        : MaterialCode(factor)
        , m_c1(c1)
        , m_c2(c2)
    {
    }

    Color MaterialCheckerBoard::getColor(const RayHit &rayhit) const
    {
        auto point = rayhit.getHitPoint();

        if ((int)(std::floor(point.getX() / m_factor)
        + std::floor(point.getZ() / m_factor)) % 2 == 0)
            return m_c1;
        else
            return m_c2;
    }
} // namespace Raytracer
