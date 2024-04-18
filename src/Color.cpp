/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Color.cpp
*/

#include "Color.hpp"

namespace Raytracer {
    Color::Color(double r = 0., double g = 0., double b = 0.)
        : m_r(std::clamp(0., 1., r))
        , m_g(std::clamp(0., 1., g))
        , m_b(std::clamp(0., 1., b))
    {
    }

    Color::Color(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0)
        : m_r(RGBToPercent(r))
        , m_g(RGBToPercent(g))
        , m_b(RGBToPercent(b))
    {
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

} // namespace Raytracer
