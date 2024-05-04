/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Checkboard.cpp
*/

#include "Scene/Materials/MaterialCode/Checkboard.hpp"

#include <cmath>

namespace Raytracer {
    MaterialCheckBoard::MaterialCheckBoard(Color c1, Color c2, size_t factor)
        : MaterialCode(factor)
        , m_c1(c1)
        , m_c2(c2)
    {
    }

    static inline bool isPair(double p)
    {
        return std::fmod(p, 2.) == 0;
    }

    Color MaterialCheckBoard::getColor(const RayHit &rayhit) const
    {
        auto point = rayhit.getHitPoint();
        bool subPair = (isPair(point.getX()) && isPair(point.getY()))
            || (!isPair(point.getX()) && !isPair(point.getY()));

        if (isPair(point.getZ()))
            return subPair ? m_c1 : m_c2;
        else
            return subPair ? m_c2 : m_c1;
    }
} // namespace Raytracer