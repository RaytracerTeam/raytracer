/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Utils.hpp
*/

#pragma once

#include <cmath>

namespace Raytracer {
    namespace Math {
        /**
        * @brief Converts degrees to radians
        * @param deg The degrees to convert
        * @return The radians
        **/
        double deg2rad(double deg);

        /**
        * @brief Converts radians to degrees
        * @param rad The radians to convert
        * @return The degrees
        **/
        double rad2deg(double rad);
    } // namespace Math

} // namespace Raytracer