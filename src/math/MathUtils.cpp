/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MathUtils.cpp
*/

#include "Math/Utils.hpp"

namespace Raytracer {
    namespace Math {
        double deg2rad(double deg)
        {
            return deg * M_PI / 180.;
        }

        double rad2deg(double rad)
        {
            return rad * 180. / M_PI;
        }
    } // namespace Math

} // namespace Raytracer
