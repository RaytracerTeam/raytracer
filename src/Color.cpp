/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Color.cpp
*/

#include "Color.hpp"

#include "Error.hpp"
#include "Math/Algorithm.hpp"
#include <algorithm>

namespace Raytracer {
    Color::Color(double r, double g, double b)
        : m_r(Math::Algorithm::clampD(r, 0., 1.))
        , m_g(Math::Algorithm::clampD(g, 0., 1.))
        , m_b(Math::Algorithm::clampD(b, 0., 1.))
    {
    }

    Color::Color(unsigned int r, unsigned int g, unsigned int b)
        : m_r(RGBToPercent(r))
        , m_g(RGBToPercent(g))
        , m_b(RGBToPercent(b))
    {
    }

    Color::Color(float *vals)
    {
        if (!vals)
            return;
        if (vals[0])
            m_r = vals[0];
        if (vals[1])
            m_g = vals[1];
        if (vals[2])
            m_b = vals[2];
    }

    double Color::operator[](uint8_t i) const
    {
        switch (i) {
        case 0:
            return getR();
        case 1:
            return getG();
        case 2:
            return getB();
        default:
            throw Error("Invalid color index", "");
        }
    }
    double &Color::operator[](uint8_t i)
    {
        switch (i) {
        case 0:
            return m_r;
        case 1:
            return m_g;
        case 2:
            return m_b;
        default:
            throw Error("Invalid color index", "");
        }
    }

    double Color::RGBToPercent(uint8_t value)
    {
        return (double)value / 255.;
    }

    uint8_t Color::PercentToRGB(double value)
    {
        return value * 255;
    }

    ////////////

    Color &Color::operator+=(const Color &right)
    {
        m_r = Math::Algorithm::clampD(m_r + right.m_r, 0., 1.);
        m_g = Math::Algorithm::clampD(m_g + right.m_g, 0., 1.);
        m_b = Math::Algorithm::clampD(m_b + right.m_b, 0., 1.);
        return *this;
    }

    Color &Color::operator*=(const Color &right)
    {
        m_r *= right.m_r;
        m_g *= right.m_g;
        m_b *= right.m_b;
        return *this;
    }

    Color Color::operator+(const Color &right) const
    {
        Color color = *this;
        color += right;
        return color;
    }

    Color Color::operator*(const Color &right) const
    {
        Color color = *this;
        color *= right;
        return color;
    }

    Color &Color::operator*=(double scalar)
    {
        m_r *= scalar;
        m_g *= scalar;
        m_b *= scalar;
        return *this;
    }

    Color &Color::operator+=(double scalar)
    {
        m_r += scalar;
        m_g += scalar;
        m_b += scalar;
        return *this;
    }

    Color Color::operator*(double scalar) const
    {
        Color color = *this;
        color *= scalar;
        return color;
    }

    Color Color::operator+(double scalar) const
    {
        Color color = *this;
        color += scalar;
        return color;
    }

    Color &Color::operator*=(const Math::Vector3D &v)
    {
        m_r *= v.getX();
        m_g *= v.getY();
        m_b *= v.getZ();
        return *this;
    }

    Color Color::operator*(const Math::Vector3D &v) const
    {
        Color color = *this;
        color *= v;
        return color;
    }

    Color &Color::operator+=(const Math::Vector3D &v)
    {
        m_r += v.getX();
        m_g += v.getY();
        m_b += v.getZ();
        return *this;
    }

    Color Color::operator+(const Math::Vector3D &v) const
    {
        Color color = *this;
        color += v;
        return color;
    }

    std::ostream &operator<<(std::ostream &os, const Color &color)
    {
        os << "Color(" << color.getR() << ", " << color.getG() << ", " << color.getB() << ")";
        return os;
    }
} // namespace Raytracer
