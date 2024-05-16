/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Angle3.cpp
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

        Angle3D::operator float *()
        {
            m_vals[0] = m_yaw;
            m_vals[1] = m_pitch;
            m_vals[2] = m_roll;
            return m_vals;
        }

        Angle3D &Angle3D::operator+=(const Angle3D &right)
        {
            m_yaw += right.m_yaw;
            m_pitch += right.m_pitch;
            m_roll += right.m_roll;

            return *this;
        }

        Angle3D Angle3D::operator+(const Angle3D &right) const
        {
            Angle3D vec = *this;
            vec += right;
            return vec;
        }

        Angle3D &Angle3D::operator-=(const Angle3D &right)
        {
            m_yaw -= right.m_yaw;
            m_pitch -= right.m_pitch;
            m_roll -= right.m_roll;

            return *this;
        }

        Angle3D Angle3D::operator-(const Angle3D &right) const
        {
            Angle3D vec = *this;
            vec -= right;
            return vec;
        }

        Angle3D &Angle3D::operator*=(double scalar)
        {
            m_yaw *= scalar;
            m_pitch *= scalar;
            m_roll *= scalar;

            return *this;
        }

        Angle3D Angle3D::operator*(double scalar) const
        {
            Angle3D vec = *this;
            vec *= scalar;
            return vec;
        }

    } // namespace Math

} // namespace Raytracer
