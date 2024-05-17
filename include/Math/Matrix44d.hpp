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
            /**
            * @brief Constructor of the Matrix44 class
            **/
            Matrix44();
            ~Matrix44() = default;

            /**
            * @brief Constructor of the Matrix44 class
            * @param m The Matrix44 to copy
            **/
            Matrix44(const Matrix44 &m);

            /**
            * @brief Constructor of the Matrix44 class
            * @param arr The array to copy
            **/
            Matrix44(std::array<std::array<double, 4>, 4> arr);

            /**
            * @brief Constructor of the Matrix44 class
            * @param rotX The yaw rotation
            * @param rotY The pitch rotation
            * @param rotZ The roll rotation
            **/
            Matrix44(double rotX, double rotY, double rotZ);

            /**
            * @brief Operator= of the Matrix44 class
            * @param m The Matrix44 to copy
            * @return The new Matrix44
            **/
            Matrix44 &operator=(const Matrix44 &m);

            /**
            * @brief Getter of the angles of rotation
            **/
            Math::Angle3D getRot() const { return m_rot; }

            /**
            * @brief Operator() of the Matrix44 class
            * @param x The x value
            * @param y The y value
            * @return The value of the matrix at the x and y position
            **/
            double operator()(uint8_t x, uint8_t y) const
            {
                return m_arr[x][y];
            }

            /**
            * @brief Operator() of the Matrix44 class
            * @param x The x value
            * @param y The y value
            * @return The value of the matrix at the x and y position
            **/
            double &operator()(uint8_t x, uint8_t y)
            {
                return m_arr[x][y];
            }

            /**
            * @brief Operator[] of the Matrix44 class
            * @param i The index
            * @return The value of the matrix at the index
            **/
            const std::array<double, 4> &operator[](uint8_t i) const { return m_arr[i]; }
            /**
            * @brief Operator[] of the Matrix44 class
            * @param i The index
            * @return The value of the matrix at the index
            **/
            std::array<double, 4> &operator[](uint8_t i) { return m_arr[i]; }

            /**
            * @brief Operator* of the Matrix44 class
            * @param src The Vector3D to multiply
            * @return The new Vector3D
            **/
            Vector3D operator*(const Vector3D &src) const;

            /**
            * @brief Operator* of the Matrix44 class
            * @param src The Matrix44 to multiply
            * @return The new Matrix44
            **/
            Matrix44 operator*(const Matrix44 &src) const;

            /**
            * @brief Operator* of the Matrix44 class
            * @param src The double to multiply
            * @return The new Matrix44
            **/
            Vector3D operator^(const Vector3D &src) const;

            /**
            * @brief Operator* of the Matrix44 class
            * @param src The array to multiply
            * @return The new Vector3D
            **/
            Vector3D operator*(const std::array<double, 4> &src) const;

            /**
            * @brief transpose the matrix
            * @return The new Matrix44
            **/
            Matrix44 transpose() const;

            /**
            * @brief inverse the matrix
            * @return The new Matrix44
            **/
            Matrix44 inverse() const;
        private:
            std::array<std::array<double, 4>, 4> m_arr; ///< The matrix
            Math::Angle3D m_rot; ///< The rotation
        };
    } // namespace Math

} // namespace Raytracer
