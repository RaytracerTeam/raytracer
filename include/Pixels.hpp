/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Pixels.hpp
*/

#pragma once

#include <stddef.h>

namespace Raytracer {
    class Dimension {
        public:
            Dimension() = default;
            Dimension(size_t width, size_t height);
            ~Dimension() = default;

            size_t getWidth(void) const { return m_width; }
            size_t getHeight(void) const { return m_height; }
            void setWidth(size_t width) { m_width = width; }
            void setHeight(size_t height) { m_height = height; }

            double getWidthD(void) const { return (double)m_width; }
            double getHeightD(void) const { return (double)m_height; }

            size_t getSize(void) const { return m_width * m_height; }
        private:
            size_t m_width;
            size_t m_height;
    };
} // namespace Raytracer
