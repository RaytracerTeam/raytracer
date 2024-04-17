/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Point3D.hpp
*/

#pragma once

#include <cstdint>

namespace Raytracer {
    namespace Math {
        class Point3D {
        public:
            Point3D(double valX = 0, double valY = 0, double valZ = 0);
            Point3D(const Point3D &right);
            ~Point3D() = default;
            Point3D &operator=(const Point3D& vec);

            double operator[](uint8_t i) const {
                switch (i) {
                    case 0:
                        return getX();
                    case 1:
                        return getY();
                    default: // case 2
                        return getZ();
                }
            }
            double &operator[](uint8_t i) {
                switch (i) {
                    case 0:
                        return x;
                    case 1:
                        return y;
                    default: // case 2
                        return z;
                }
            }

            double getX(void) const { return x; }
            double getY(void) const { return y; }
            double getZ(void) const { return z; }

            void setX(double val) { x = val; }
            void setY(double val) { y = val; }
            void setZ(double val) { z = val; }

            //////////////////////////

            constexpr Point3D &operator+=(const Point3D &right);
            constexpr Point3D &operator-=(const Point3D &right);
            constexpr Point3D &operator*=(double scalar);
            constexpr Point3D &operator*=(const Point3D &right);
            constexpr Point3D &operator/=(double scalar);
            constexpr Point3D &operator/=(const Point3D &right);

            Point3D operator+(const Point3D &right) const;
            Point3D operator-(const Point3D &right) const;
            Point3D operator*(double scalar) const;
            Point3D operator*(const Point3D &right) const;
            Point3D operator/(double scalar) const;
            Point3D operator/(const Point3D &right) const;

            constexpr bool operator==(const Point3D &right);
            constexpr bool operator!=(const Point3D &right);

        protected:
            double x;
            double y;
            double z;
        };
    }
}
