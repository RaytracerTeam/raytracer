/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vector3D.cpp
*/

#include "Math/Vector3D.hpp"
#include "Error.hpp"
#include <cmath>

namespace Raytracer {
    namespace Math {
        Vector3D::Vector3D(double valX, double valY, double valZ)
        {
            x = valX;
            y = valY;
            z = valZ;
        }

        Vector3D::Vector3D(const Vector3D &right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
        }

        Vector3D &Vector3D::operator=(const Vector3D& vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            return *this;
        }

        double Vector3D::length(void) const
        {
            return std::sqrt(dot(*this));
        }

        double Vector3D::dot(const Vector3D &v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        Vector3D Vector3D::normalize(void) const
        {
            double len = length();
            return *this / len;
        }

        Vector3D Vector3D::cross(const Vector3D &v) const
        {
            return Vector3D(
                (y * v.z) - (z * v.y),
                (z * v.x) - (x * v.z),
                (x * v.y) - (y * v.x));
        }

        constexpr Vector3D &Vector3D::operator+=(const Vector3D &right)
        {
            x += right.x;
            y += right.y;
            z += right.z;

            return *this;
        }

        constexpr Vector3D &Vector3D::operator-=(const Vector3D &right)
        {
            x -= right.x;
            y -= right.y;
            z -= right.z;

            return *this;
        }

        constexpr Vector3D &Vector3D::operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        constexpr Vector3D &Vector3D::operator*=(const Vector3D &right)
        {
            x *= right.x;
            y *= right.y;
            z *= right.z;

            return *this;
        }

        constexpr Vector3D &Vector3D::operator/=(double scalar)
        {
            if (scalar == 0)
                throw Error("Cannot divide by 0", "Math::Vector3D");
            x /= scalar;
            y /= scalar;
            z /= scalar;

            return *this;
        }

        constexpr Vector3D &Vector3D::operator/=(const Vector3D &right)
        {
            if (right.x == 0 || right.y == 0 || right.z == 0)
                throw Error("Cannot divide by 0", "Math::Vector3D");
            x /= right.x;
            y /= right.y;
            z /= right.z;

            return *this;
        }

        Vector3D Vector3D::operator+(const Vector3D &right) const
        {
            Vector3D vec = *this;
            vec += right;
            return vec;
        }

        Vector3D Vector3D::operator-(const Vector3D &right) const
        {
            Vector3D vec = *this;
            vec -= right;
            return vec;
        }

        Vector3D Vector3D::operator*(const Vector3D &right) const
        {
            Vector3D vec = *this;
            vec *= right;
            return vec;
        }

        Vector3D Vector3D::operator*(double scalar) const
        {
            Vector3D vec = *this;
            vec *= scalar;
            return vec;
        }

        Vector3D Vector3D::operator/(double scalar) const
        {
            Vector3D vec = *this;
            vec /= scalar;
            return vec;
        }

        Vector3D Vector3D::operator/(const Vector3D &right) const
        {
            Vector3D vec = *this;
            vec /= right;
            return vec;
        }

        constexpr bool Vector3D::operator==(const Vector3D &right)
        {
            return (x == right.x) && (y == right.y) && (z == right.z);
        }

        constexpr bool Vector3D::operator!=(const Vector3D &right)
        {
            return !(*this == right);
        }

        //////////////////////

        double Vector3D::gDist(const Vector3D &left, const Vector3D &right)
        {
            return std::sqrt(
                std::pow(left.x - right.x, 2) +
                std::pow(left.y - right.y, 2) +
                std::pow(left.z - right.z, 2)
            );
        }

        double Vector3D::gDot(const Vector3D &left, const Vector3D &right)
        {
            return left.x * right.x + left.y * right.y + left.z * right.z;
        }

        Vector3D Vector3D::gLerp(const Vector3D &left, const Vector3D &right, double t)
        {
            return left + (right - left) * t;
        }

    } // namespace Math

} // namespace Raytracer
