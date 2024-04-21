/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Algorithm
*/

#include "Math/Algorithm.hpp"

namespace Raytracer
{
    namespace Math {
        double Algorithm::clampD(double value, double min, double max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;
            return value;
        }
    }
} // namespace Raytracer
