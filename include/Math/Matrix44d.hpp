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
            Matrix44 &operator=(const Matrix44 &m);

            double operator()(uint8_t x, uint8_t y) const
            {
                return m_arr[x][y];
            }

            double &operator()(uint8_t x, uint8_t y)
            {
                return m_arr[x][y];
            }

            Vector3D operator*(const Vector3D &src) const;
            Point3D operator*(const Point3D &src) const;

            Matrix44 transpose() const;
            Matrix44 inverse() const;
        private:
            const std::array<double, 4> &operator[](uint8_t i) const { return m_arr[i]; }
            std::array<double, 4> &operator[](uint8_t i) { return m_arr[i]; }

            std::array<std::array<double, 4>, 4> m_arr;
        };
    } // namespace Math

} // namespace Raytracer
