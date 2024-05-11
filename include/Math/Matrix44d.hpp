/*
** EPIdoubleECH PROJECdouble, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Matrix44d.hpp
*/

#pragma once

#include <array>
#include <cstdint>
#include <stddef.h>

#include "Vector3D.hpp"

namespace Raytracer {
    namespace Math {
        class Matrix44 {
        public:
            Matrix44();
            ~Matrix44() = default;
            Matrix44(const Matrix44 &m);
            Matrix44(std::array<std::array<double, 4>, 4> arr);
            Matrix44(double rotX, double rotY, double rotZ);
            Matrix44 &operator=(const Matrix44 &m);

            Math::Angle3D getRot() const { return m_rot; }
            Math::Vector3D getScaling() const { return m_scaling;}
            void setScaling(Math::Vector3D scaling);

            double operator()(uint8_t x, uint8_t y) const
            {
                return m_arr[x][y];
            }

            double &operator()(uint8_t x, uint8_t y)
            {
                return m_arr[x][y];
            }

            const std::array<double, 4> &operator[](uint8_t i) const { return m_arr[i]; }
            std::array<double, 4> &operator[](uint8_t i) { return m_arr[i]; }

            Vector3D operator*(const Vector3D &src) const;
            Matrix44 operator*(const Matrix44 &src) const;
            Vector3D operator^(const Vector3D &src) const;
            Vector3D operator*(const std::array<double, 4> &src) const;

            Matrix44 transpose() const;
            Matrix44 inverse() const;

        private:
            std::array<std::array<double, 4>, 4> m_arr;
            Math::Angle3D m_rot;
            Vector3D m_scaling = { 1, 1, 1 };
    };
    } // namespace Math

} // namespace Raytracer
