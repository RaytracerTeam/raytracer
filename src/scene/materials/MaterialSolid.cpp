/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialSolid.cpp
*/

#include "Scene/Materials/MaterialSolid.hpp"

#include <cmath>

namespace Raytracer {
    MaterialSolid::MaterialSolid(const Color &color)
    {
        m_color = color;
    }

    Color MaterialSolid::getColor(const RayHit &) const
    {
        return m_color;
    }
} // namespace Raytracer
