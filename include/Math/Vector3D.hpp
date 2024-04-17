/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vetor3.h
*/

#pragma once

#include "Point3D.hpp"

namespace Raytracer {
    namespace Math {
        class Vector3D : public Point3D {
        public:
            Vector3D(double valX = 0, double valY = 0, double valZ = 0);
            Vector3D(const Vector3D &right);
            ~Vector3D() = default;
            Vector3D &operator=(const Vector3D& vec);

            double length(void) const;
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

            static double gDist(const Vector3D &left, const Vector3D &right);
            static double gDot(const Vector3D &left, const Vector3D &right);

            // interpolation for camera movements
            static Vector3D gLerp(const Vector3D &left, const Vector3D &right, double t);
        };
    } // namespace Math

} // namespace Raytracer
