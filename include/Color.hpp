/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Color.hpp
*/

#pragma once

#include <cstdint>

#include "Error.hpp"

namespace Raytracer {
    class Color {
    public:
        Color(uint8_t a = 255, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
            : m_a(a)
            , m_r(r)
            , m_g(g)
            , m_b(b)
        {
        }
        ~Color() = default;

        uint8_t operator[](uint8_t i) const
        {
            switch (i) {
            case 0:
                return getAlpha();
            case 1:
                return getR();
            case 2:
                return getG();
            case 3:
                return getB();
            default:
                throw Error("Invalid color index", "");
            }
        }
        uint8_t &operator[](uint8_t i)
        {
            switch (i) {
            case 0:
                return m_a;
            case 1:
                return m_r;
            case 2:
                return m_g;
            case 3:
                return m_b;
            default:
                throw Error("Invalid color index", "");
            }
        }

        uint8_t getAlpha(void) const { return m_a; }
        uint8_t getR(void) const { return m_r; }
        uint8_t getG(void) const { return m_g; }
        uint8_t getB(void) const { return m_b; }

    private:
        uint8_t m_a;
        uint8_t m_r;
        uint8_t m_g;
        uint8_t m_b;
    };
} // namespace Raytracer
