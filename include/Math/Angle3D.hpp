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
            ~Angle3D() = default;
            // Angle3D &operator=(const Angle3D &angle);

            double getYaw(void) const { return m_yaw; }
            double getPitch(void) const { return m_pitch; }
            double getRoll(void) const { return m_roll; }

            void setYam(double a) { m_yaw = a; }
            void setPitch(double a) { m_pitch = a; }
            void setRoll(double a) { m_roll = a; }
        private:
            double m_yaw = 0; /* x axis */
            double m_pitch = 0; /* y axis */
            double m_roll = 0; /* z axis */
        };
    } // namespace Math

} // namespace Raytracer
