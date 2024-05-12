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

    MaterialSolid::MaterialSolid(const MaterialSolid &src)
    {
        m_color = src.m_color;
        m_reflection = src.m_reflection;
        m_emission = src.m_emission;
        m_transparency = src.m_transparency;
        m_fuzz = src.m_fuzz;
        m_refractionIndex = src.m_refractionIndex;
    }

    Color MaterialSolid::getColor(const RayHit &) const
    {
        return m_color;
    }
} // namespace Raytracer
