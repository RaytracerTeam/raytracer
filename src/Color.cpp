/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Color.cpp
*/

#include "Color.hpp"

namespace Raytracer {
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
