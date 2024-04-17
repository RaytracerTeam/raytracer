/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Angle.hpp
*/

#pragma once

#include "Vector3D.hpp"

namespace Raytracer {
    namespace Math {
        class Angle3D {
        public:
            Angle3D(double x = 0, double y = 0, double z = 0);
        private:
            double yaw = 0; /* x axis */
            double pitch = 0; /* y axis */
            double roll = 0; /* z axis */
        };
    } // namespace Math

} // namespace Raytracer
