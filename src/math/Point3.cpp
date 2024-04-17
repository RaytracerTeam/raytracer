/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Point3.cpp
*/

#include "Error.hpp"
#include "Math/Point3D.hpp"
#include <cmath>

namespace Raytracer {
    namespace Math {
        Point3D::Point3D(double valX, double valY, double valZ)
        {
            x = valX;
            y = valY;
            z = valZ;
        }

        Point3D::Point3D(const Point3D &right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
        }

        Point3D &Point3D::operator=(const Point3D &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            return *this;
        }

        constexpr Point3D &Point3D::operator+=(const Point3D &right)
        {
            x += right.x;
            y += right.y;
            z += right.z;

            return *this;
        }

        constexpr Point3D &Point3D::operator-=(const Point3D &right)
        {
            x -= right.x;
            y -= right.y;
            z -= right.z;

            return *this;
        }

        constexpr Point3D &Point3D::operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        constexpr Point3D &Point3D::operator*=(const Point3D &right)
        {
            x *= right.x;
            y *= right.y;
            z *= right.z;

            return *this;
        }

        constexpr Point3D &Point3D::operator/=(double scalar)
        {
            if (scalar == 0)
                throw Error("Cannot divide by 0", "Math::Point3D");
            x /= scalar;
            y /= scalar;
            z /= scalar;

            return *this;
        }

        constexpr Point3D &Point3D::operator/=(const Point3D &right)
        {
            if (right.x == 0 || right.y == 0 || right.z == 0)
                throw Error("Cannot divide by 0", "Math::Point3D");
            x /= right.x;
            y /= right.y;
            z /= right.z;

            return *this;
        }

        Point3D Point3D::operator+(const Point3D &right) const
        {
            Point3D vec = *this;
            vec += right;
            return vec;
        }

        Point3D Point3D::operator-(const Point3D &right) const
        {
            Point3D vec = *this;
            vec -= right;
            return vec;
        }

        Point3D Point3D::operator*(const Point3D &right) const
        {
            Point3D vec = *this;
            vec *= right;
            return vec;
        }

        Point3D Point3D::operator*(double scalar) const
        {
            Point3D vec = *this;
            vec *= scalar;
            return vec;
        }

        Point3D Point3D::operator/(double scalar) const
        {
            Point3D vec = *this;
            vec /= scalar;
            return vec;
        }

        Point3D Point3D::operator/(const Point3D &right) const
        {
            Point3D vec = *this;
            vec /= right;
            return vec;
        }

        constexpr bool Point3D::operator==(const Point3D &right)
        {
            return (x == right.x) && (y == right.y) && (z == right.z);
        }

        constexpr bool Point3D::operator!=(const Point3D &right)
        {
            return !(*this == right);
        }

        //////////////////////////////////

        double Point3D::dot(const Point3D &v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

    } // namespace Math

} // namespace Raytracer
