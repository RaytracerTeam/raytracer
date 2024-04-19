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
            m_yaw = valX;
            m_pitch = valY;
            m_roll = valZ;
        }

    } // namespace Math

} // namespace Raytracer
