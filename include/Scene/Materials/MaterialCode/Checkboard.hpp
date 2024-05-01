/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Checkboard.hpp
*/


#pragma once

#include "Scene/Materials/MaterialCode.hpp"

namespace Raytracer {
    class MaterialCheckBoard : public MaterialCode {
    public:
        MaterialCheckBoard(Color c1 = {255U, 255, 255}, Color c2 = {0U, 0, 0}, size_t factor = 3);
        ~MaterialCheckBoard() = default;

        Color getColor(const RayHit &rayhit) const override;
    private:
        Color m_c1;
        Color m_c2;
    };
} // namespace Raytracer
