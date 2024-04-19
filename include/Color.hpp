/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Color.hpp
*/

#pragma once

#include <cstdint>

namespace Raytracer {
    class Color {
    public:
        Color() = default;
        Color(double r, double g, double b);
        Color(unsigned int r, unsigned int g, unsigned int b);
        ~Color() = default;

        double operator[](uint8_t i) const;
        double &operator[](uint8_t i);

        double getR(void) const { return m_r; }
        double getG(void) const { return m_g; }
        double getB(void) const { return m_b; }

        static double RGBToPercent(uint8_t value);
        static uint8_t PercentToRGB(double value);
    private:
        double m_r;
        double m_g;
        double m_b;
    };
} // namespace Raytracer
