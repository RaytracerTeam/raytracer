/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialCode.cpp
*/

#include "Scene/Materials/MaterialCode.hpp"

#include <cmath>

namespace Raytracer {
    MaterialCode::MaterialCode(Color (&colorCode)(const RayHit &))
    {
        m_colorCode = colorCode;
    }

    Color MaterialCode::getColor(const RayHit &rayhit) const
    {
        return m_colorCode(rayhit);
    }
} // namespace Raytracer
