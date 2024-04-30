/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Color.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"

#include <cstdint>

namespace Raytracer {
    class Color {
    public:
        Color() = default;
        Color(double r, double g, double b);
        Color(unsigned int r, unsigned int g, unsigned int b);
        Color(float *vals);
        ~Color() = default;

        double operator[](uint8_t i) const;
        double &operator[](uint8_t i);

        double getR(void) const { return m_r; }
        double getG(void) const { return m_g; }
        double getB(void) const { return m_b; }

        static double RGBToPercent(uint8_t value);
        static uint8_t PercentToRGB(double value);

        ////////////

        Color &operator+=(const Color &right);
        Color &operator*=(const Color &right);
        Color &operator*=(const Math::Vector3D &right);
        Color &operator*=(double scalar);

        Color operator+(const Color &right) const;
        Color operator*(const Math::Vector3D &right) const;
        Color operator*(const Color &right) const;
        Color operator*(double scalar) const;

    private:
        double m_r = 0;
        double m_g = 0;
        double m_b = 0;
    };
} // namespace Raytracer

std::ostream &operator<<(std::ostream &os, const Raytracer::Color &color);
