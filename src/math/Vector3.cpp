/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vector3.cpp
*/

#include "Error.hpp"
#include "Math/Utils.hpp"
#include "Math/Vector3D.hpp"

#include <cmath>

namespace Raytracer {
    namespace Math {
        Vector3D::Vector3D(double valX, double valY, double valZ)
        {
            x = valX;
            y = valY;
            z = valZ;
        }

        Vector3D::Vector3D(const Vector3D &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }

        Vector3D::Vector3D(float *vals)
        {
            if (!vals)
                return;
            if (vals[0])
                x = vals[0];
            if (vals[1])
                y = vals[1];
            if (vals[2])
                z = vals[2];
        }

        Vector3D &Vector3D::operator=(const Vector3D &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            return *this;
        }

        Vector3D::operator float *()
        {
            m_vals[0] = x;
            m_vals[1] = y;
            m_vals[2] = z;
            return m_vals;
        }

        double Vector3D::dot(const Vector3D &v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        double Vector3D::length(void) const
        {
            return std::sqrt(dot(*this));
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

        Vector3D Vector3D::rotate(const Angle3D &angle)
        {
            return gRotate(*this, angle);
        }

        double Vector3D::angle(const Vector3D &right)
        {
            return gAngle(*this, right);
        }

        //////////////////////////

        Vector3D &Vector3D::operator+=(const Vector3D &right)
        {
            x += right.x;
            y += right.y;
            z += right.z;

            return *this;
        }

        Vector3D &Vector3D::operator-=(const Vector3D &right)
        {
            x -= right.x;
            y -= right.y;
            z -= right.z;

            return *this;
        }

        Vector3D &Vector3D::operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        Vector3D &Vector3D::operator*=(const Vector3D &right)
        {
            x *= right.x;
            y *= right.y;
            z *= right.z;

            return *this;
        }

        Vector3D &Vector3D::operator/=(double scalar)
        {
            if (scalar == 0)
                throw Error("Cannot divide by 0", "Math::Vector3D");
            x /= scalar;
            y /= scalar;
            z /= scalar;

            return *this;
        }

        Vector3D &Vector3D::operator/=(const Vector3D &right)
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

        Vector3D Vector3D::operator+(double num) const
        {
            Vector3D vec = *this;
            vec.x += num;
            vec.y += num;
            vec.z += num;
            return vec;
        }

        Vector3D Vector3D::operator-(double num) const
        {
            Vector3D vec = *this;
            vec.x -= num;
            vec.y -= num;
            vec.z -= num;
            return vec;
        }

        Vector3D Vector3D::operator-(const Vector3D &right) const
        {
            Vector3D vec = *this;
            vec -= right;
            return vec;
        }

        Vector3D Vector3D::operator-() const
        {
            Vector3D vec = *this;
            vec.x = -vec.x;
            vec.y = -vec.y;
            vec.z = -vec.z;
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

        bool Vector3D::operator==(const Vector3D &right)
        {
            return (x == right.x) && (y == right.y) && (z == right.z);
        }

        bool Vector3D::operator!=(const Vector3D &right)
        {
            return !(*this == right);
        }

        //////////////////////

        double Vector3D::gDist(const Vector3D &left, const Vector3D &right)
        {
            return std::sqrt(
                std::pow(left.x - right.x, 2) + std::pow(left.y - right.y, 2) + std::pow(left.z - right.z, 2));
        }

        double Vector3D::gDot(const Vector3D &left, const Vector3D &right)
        {
            return left.x * right.x + left.y * right.y + left.z * right.z;
        }

        Vector3D Vector3D::gRotate(const Vector3D &v, const Math::Angle3D &angle)
        {
            double yawRads = Math::deg2rad(angle.getYaw());
            double pitchRads = Math::deg2rad(angle.getPitch());

            double y = (v.y * std::cos(pitchRads) - v.z * std::sin(pitchRads));
            double z = (v.y * std::sin(pitchRads) + v.z * std::cos(pitchRads));
            double x = (v.x * std::cos(yawRads) + z * std::sin(yawRads));
            z = (-v.x * std::sin(yawRads) + z * std::cos(yawRads));
            return Vector3D(x, y, z);
        }

        double Vector3D::gAngle(const Vector3D &left, const Vector3D &right)
        {
            double cosAngle = left.dot(right) / (left.length() * right.length());
            return rad2deg(std::acos(cosAngle));
        }

        Vector3D Vector3D::gLerp(const Vector3D &left, const Vector3D &right, double t)
        {
            return left + (right - left) * t;
        }

        Math::Vector3D Vector3D::gReflect(const Math::Vector3D &left, const Math::Vector3D &right)
        {
            return left - (right * 2 * left.dot(right));
        }
    } // namespace Math
} // namespace Raytracer

std::ostream &operator<<(std::ostream &os, const Raytracer::Math::Vector3D &v)
{
    os << "Vector3D(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
    return os;
}
