/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vetor3.h
*/

#pragma once

namespace Raytracer {
    namespace Math {
        class Vector3 {
        public:
            constexpr Vector3(double valX, double valY, double valZ);
            constexpr Vector3(const Vector3 &right);
            ~Vector3() = default;

            constexpr double length(void) const;
            constexpr double dot(const Vector3 &v) const;
            constexpr Vector3 cross(const Vector3 &v) const;

            constexpr Vector3 normalize(void) const;

            constexpr Vector3 &operator+=(const Vector3 &right);
            constexpr Vector3 &operator-=(const Vector3 &right);
            constexpr Vector3 &operator*=(double scalar);
            constexpr Vector3 &operator*=(const Vector3 &right);
            constexpr Vector3 &operator/=(double scalar);
            constexpr Vector3 &operator/=(const Vector3 &right);

            constexpr Vector3 operator+(const Vector3 &right) const;
            constexpr Vector3 operator-(const Vector3 &right) const;
            constexpr Vector3 operator*(double scalar) const;
            constexpr Vector3 operator*(const Vector3 &right) const;
            constexpr Vector3 operator/(double scalar) const;
            constexpr Vector3 operator/(const Vector3 &right) const;

            constexpr bool operator==(const Vector3 &right);
            constexpr bool operator!=(const Vector3 &right);

        private:
            double x;
            double y;
            double z;
        };
    } // namespace Math

} // namespace Raytracer
