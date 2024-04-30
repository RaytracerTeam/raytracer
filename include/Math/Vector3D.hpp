/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vetor3.h
*/

#pragma once

#include <cstdint>
#include <iostream>

#include "Error.hpp"
#include "Angle3D.hpp"

namespace Raytracer {
    namespace Math {
        class Vector3D {
        public:
            Vector3D(double valX = 0, double valY = 0, double valZ = 0);
            Vector3D(const Vector3D &right);
            Vector3D(float *vals);
            ~Vector3D() = default;
            Vector3D &operator=(const Vector3D &vec);

            double operator[](uint8_t i) const
            {
                switch (i) {
                case 0:
                    return getX();
                case 1:
                    return getY();
                case 2:
                    return getZ();
                default:
                    throw Error("Invalid point index", "");
                }
            }
            double &operator[](uint8_t i)
            {
                switch (i) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                default:
                    throw Error("Invalid point index", "");
                }
            }

            double getX(void) const { return x; }
            double getY(void) const { return y; }
            double getZ(void) const { return z; }

            void setX(double val) { x = val; }
            void setY(double val) { y = val; }
            void setZ(double val) { z = val; }

            //////////////////////////

            Vector3D &operator+=(const Vector3D &right);
            Vector3D &operator-=(const Vector3D &right);
            Vector3D &operator*=(double scalar);
            Vector3D &operator*=(const Vector3D &right);
            Vector3D &operator/=(double scalar);
            Vector3D &operator/=(const Vector3D &right);

            Vector3D operator+(const Vector3D &right) const;
            Vector3D operator-() const;
            Vector3D operator-(const Vector3D &right) const;
            Vector3D operator*(double scalar) const;
            Vector3D operator*(const Vector3D &right) const;
            Vector3D operator/(double scalar) const;
            Vector3D operator/(const Vector3D &right) const;

            bool operator==(const Vector3D &right);
            bool operator!=(const Vector3D &right);

            //////////////////////////

            double dot(const Vector3D &v) const;
            double length(void) const;
            Vector3D cross(const Vector3D &v) const;
            Vector3D normalize(void) const;
            Vector3D rotate(const Angle3D &angle);
            double angle(const Vector3D &right);

            //////////////////////////

            static double gDist(const Vector3D &left, const Vector3D &right);
            static double gDot(const Vector3D &left, const Vector3D &right);
            static Vector3D gRotate(const Vector3D &left, const Angle3D &right);
            static double gAngle(const Vector3D &left, const Vector3D &right);

            // interpolation for camera movements
            static Vector3D gLerp(const Vector3D &left, const Vector3D &right, double t);

        private:
            double x;
            double y;
            double z;
        };

    } // namespace Math
} // namespace Raytracer

std::ostream &operator<<(std::ostream &os, const Raytracer::Math::Vector3D &v);
