/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Checkerboard.hpp
*/


#pragma once

#include "Scene/Materials/MaterialCode.hpp"

namespace Raytracer {
    class MaterialCheckerBoard : public MaterialCode {
    public:
        MaterialCheckerBoard(Color c1 = {255U, 255, 255}, Color c2 = {0U, 0, 0}, float factor = 1);
        ~MaterialCheckerBoard() = default;

        MaterialType getType(void) const override { return MaterialType::CHECKERBOARD; };

        Color getColor(const RayHit &rayhit) const override;

        void setC1(Color c1) { m_c1 = c1; }
        void setC2(Color c2) { m_c2 = c2; }

        Color getC1() const { return m_c1; }
        Color getC2() const { return m_c2; }
    private:
        Color m_c1;
        Color m_c2;
    };
} // namespace Raytracer
