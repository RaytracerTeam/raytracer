/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vector3.cpp
*/

#include "Math/Vector3.hpp"
#include "Math/Error.hpp"
#include <cmath>

namespace Raytracer {
    namespace Math {
        constexpr Vector3::Vector3(double valX, double valY, double valZ)
        {
            x = valX;
            y = valY;
            z = valZ;
        }

        constexpr Vector3::Vector3(const Vector3 &right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
        }

        constexpr double Vector3::length(void) const
        {
            return std::sqrt(dot(*this));
        }

        constexpr double Vector3::dot(const Vector3 &v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        constexpr Vector3 Vector3::normalize(void) const
        {
            double len = length();
            return *this / len;
        }

        constexpr Vector3 Vector3::cross(const Vector3 &v) const
        {
            return Vector3(
                (y * v.z) - (z * v.y),
                (z * v.x) - (x * v.z),
                (x * v.y) - (y * v.x));
        }

        constexpr Vector3 &Vector3::operator+=(const Vector3 &right)
        {
            x += right.x;
            y += right.y;
            z += right.z;

            return *this;
        }

        constexpr Vector3 &Vector3::operator-=(const Vector3 &right)
        {
            x -= right.x;
            y -= right.y;
            z -= right.z;

            return *this;
        }

        constexpr Vector3 &Vector3::operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        constexpr Vector3 &Vector3::operator*=(const Vector3 &right)
        {
            x *= right.x;
            y *= right.y;
            z *= right.z;

            return *this;
        }

        constexpr Vector3 &Vector3::operator/=(double scalar)
        {
            if (scalar == 0)
                throw Error("Cannot divide by 0", "Math::Vector3");
            x /= scalar;
            y /= scalar;
            z /= scalar;

            return *this;
        }

        constexpr Vector3 &Vector3::operator/=(const Vector3 &right)
        {
            if (right.x == 0 || right.y == 0 || right.z == 0)
                throw Error("Cannot divide by 0", "Math::Vector3");
            x /= right.x;
            y /= right.y;
            z /= right.z;

            return *this;
        }

        constexpr Vector3 Vector3::operator+(const Vector3 &right) const
        {
            Vector3 vec = *this;
            vec += right;
            return vec;
        }

        constexpr Vector3 Vector3::operator-(const Vector3 &right) const
        {
            Vector3 vec = *this;
            vec -= right;
            return vec;
        }

        constexpr Vector3 Vector3::operator*(const Vector3 &right) const
        {
            Vector3 vec = *this;
            vec *= right;
            return vec;
        }

        constexpr Vector3 Vector3::operator*(double scalar) const
        {
            Vector3 vec = *this;
            vec *= scalar;
            return vec;
        }

        constexpr Vector3 Vector3::operator/(double scalar) const
        {
            Vector3 vec = *this;
            vec /= scalar;
            return vec;
        }

        constexpr Vector3 Vector3::operator/(const Vector3 &right) const
        {
            Vector3 vec = *this;
            vec /= right;
            return vec;
        }

        constexpr bool Vector3::operator==(const Vector3 &right)
        {
            return (x == right.x) && (y == right.y) && (z == right.z);
        }

        constexpr bool Vector3::operator!=(const Vector3 &right)
        {
            return !(*this == right);
        }
    } // namespace Math

} // namespace Raytracer
