/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Matrix44d.cpp
*/

#include "Math/Matrix44d.hpp"
#include <cmath>

namespace Raytracer {
    namespace Math {
        Matrix44::Matrix44(std::array<std::array<double, 4>, 4> arr)
            : m_arr(arr)
        {
        }

        Matrix44::Matrix44()
            : m_arr(
              { { { 1, 0, 0, 0 },
                  { 0, 1, 0, 0 },
                  { 0, 0, 1, 0 },
                  { 0, 0, 0, 1 } } })
        {
        }


        Matrix44::Matrix44(double rotX, double rotY, double rotZ)
        {
            m_rot = { rotX, rotY, rotZ };
            rotX = rotX * M_PI / 180;
            rotY = rotY * M_PI / 180;
            rotZ = rotZ * M_PI / 180;
            Matrix44 m1(
                { { { 1, 0, 0, 0 },
                    { 0, cos(rotX), -sin(rotX), 0 },
                    { 0, sin(rotX), cos(rotX), 0 },
                    { 0, 0, 0, 1 } } });
            Matrix44 m2(
                { { { cos(rotY), 0, sin(rotY), 0 },
                    { 0, 1, 0, 0 },
                    { -sin(rotY), 0, cos(rotY), 0 },
                    { 0, 0, 0, 1 } } });

            Matrix44 m3(
                { { { cos(rotZ), -sin(rotZ), 0, 0 },
                    { sin(rotZ), cos(rotZ), 0, 0 },
                    { 0, 0, 1, 0 },
                    { 0, 0, 0, 1 } } });
            Matrix44 m12 = m1 * m2;
            *this = m12 * m3;
        }

        Matrix44::Matrix44(const Matrix44 &m)
        {
            m_arr = m.m_arr;
        }

        Matrix44 &Matrix44::operator=(const Matrix44 &m)
        {
            m_arr = m.m_arr;
            return *this;
        }

        /* Vector distance operation */
        Vector3D Matrix44::operator*(const Vector3D &src) const
        {
            double x = src[0] * m_arr[0][0] + src[1] * m_arr[1][0] + src[2] * m_arr[2][0];
            double y = src[0] * m_arr[0][1] + src[1] * m_arr[1][1] + src[2] * m_arr[2][1];
            double z = src[0] * m_arr[0][2] + src[1] * m_arr[1][2] + src[2] * m_arr[2][2];
            return Vector3D(x, y, z);
        }

        /* Matrix multiplication operation */
        Matrix44 Matrix44::operator*(const Matrix44 &src) const
        {
            Matrix44 m;
            for (uint8_t i = 0; i < 4; ++i)
                for (uint8_t j = 0; j < 4; ++j)
                    m[i][j] = m_arr[i][0] * src[0][j] + m_arr[i][1] * src[1][j] + m_arr[i][2] * src[2][j] + m_arr[i][3] * src[3][j];
            return m;
        }

        /* Vector Point operation */
        Vector3D Matrix44::operator^(const Vector3D &src) const
        {
            double a = src[0] * m_arr[0][0] + src[1] * m_arr[1][0] + src[2] * m_arr[2][0] + m_arr[3][0];
            double b = src[0] * m_arr[0][1] + src[1] * m_arr[1][1] + src[2] * m_arr[2][1] + m_arr[3][1];
            double c = src[0] * m_arr[0][2] + src[1] * m_arr[1][2] + src[2] * m_arr[2][2] + m_arr[3][2];
            double w = src[0] * m_arr[0][3] + src[1] * m_arr[1][3] + src[2] * m_arr[2][3] + m_arr[3][3];

            return Vector3D(a / w, b / w, c / w);
        }

        Matrix44 Matrix44::transpose() const
        {
            Matrix44 m;

            for (uint8_t i = 0; i < 4; ++i)
                for (uint8_t j = 0; j < 4; ++j)
                    m[i][j] = m_arr[j][i];

            return m;
        }

        Matrix44 Matrix44::inverse() const
        {
            Matrix44 s;
            Matrix44 t(*this);

            // Forward elimination
            for (size_t i = 0; i < 3; i++) {
                int64_t pivot = i;

                double pivotsize = t[i][i];

                if (pivotsize < 0)
                    pivotsize = -pivotsize;

                for (size_t j = i + 1; j < 4; j++) {
                    double tmp = t[j][i];

                    if (tmp < 0)
                        tmp = -tmp;

                    if (tmp > pivotsize) {
                        pivot = j;
                        pivotsize = tmp;
                    }
                }

                if (pivotsize == 0) // can't invert singular matrix
                    return Matrix44();

                if (pivot != (int64_t)i) {
                    for (size_t j = 0; j < 4; j++) {
                        double tmp = t[i][j];
                        t[i][j] = t[pivot][j];
                        t[pivot][j] = tmp;

                        tmp = s[i][j];
                        s[i][j] = s[pivot][j];
                        s[pivot][j] = tmp;
                    }
                }

                for (size_t j = i + 1; j < 4; j++) {
                    double f = t[j][i] / t[i][i];

                    for (size_t k = 0; k < 4; k++) {
                        t[j][k] -= f * t[i][k];
                        s[j][k] -= f * s[i][k];
                    }
                }
            }

            // Backward substitution
            for (int64_t i = 3; i >= 0; i--) {
                double f;

                if ((f = t[i][i]) == 0) {
                    // Cannot invert singular matrix
                    return Matrix44();
                }

                for (size_t j = 0; j < 4; j++) {
                    t[i][j] /= f;
                    s[i][j] /= f;
                }

                for (size_t j = 0; (int64_t)j < i; j++) {
                    f = t[j][i];

                    for (size_t k = 0; k < 4; k++) {
                        t[j][k] -= f * t[i][k];
                        s[j][k] -= f * s[i][k];
                    }
                }
            }

            return s;
        }

    } // namespace Math

} // namespace Raytracer
