/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vetor3.h
*/

#pragma once

namespace Raytracer {
    namespace Math {
        class Vector3D {
        public:
            Vector3D(double valX, double valY, double valZ);
            Vector3D(const Vector3D &right);
            ~Vector3D() = default;

            Vector3D &operator=(const Vector3D& vec);

            double length(void) const;
            constexpr double dot(const Vector3D &v) const;
            Vector3D cross(const Vector3D &v) const;

            Vector3D normalize(void) const;

            constexpr Vector3D &operator+=(const Vector3D &right);
            constexpr Vector3D &operator-=(const Vector3D &right);
            constexpr Vector3D &operator*=(double scalar);
            constexpr Vector3D &operator*=(const Vector3D &right);
            constexpr Vector3D &operator/=(double scalar);
            constexpr Vector3D &operator/=(const Vector3D &right);

            Vector3D operator+(const Vector3D &right) const;
            Vector3D operator-(const Vector3D &right) const;
            Vector3D operator*(double scalar) const;
            Vector3D operator*(const Vector3D &right) const;
            Vector3D operator/(double scalar) const;
            Vector3D operator/(const Vector3D &right) const;

            constexpr bool operator==(const Vector3D &right);
            constexpr bool operator!=(const Vector3D &right);

            //////////////////////

            double getX(void) const { return x; }
            double getY(void) const { return y; }
            double getZ(void) const { return z; }

        private:
            double x;
            double y;
            double z;
        };
    } // namespace Math

} // namespace Raytracer
