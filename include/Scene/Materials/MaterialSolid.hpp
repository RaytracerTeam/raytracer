/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialSolid.hpp
*/

#pragma once

#include "AMaterial.hpp"

namespace Raytracer {
    class MaterialSolid : public AMaterial {
    public:
        MaterialSolid(const Color &color);
        ~MaterialSolid() = default;

        Color getColor(const RayHit &rayhit) const override;

    private:
        Color m_color;
    };
} // namespace Raytracer
