/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vector3D.cpp
*/

#include "Math/Angle3D.hpp"

namespace Raytracer {
    namespace Math {
        Angle3D::Angle3D(double valX, double valY, double valZ)
        {
            yaw = valX;
            pitch = valY;
            roll = valZ;
        }
    } // namespace Math

} // namespace Raytracer
