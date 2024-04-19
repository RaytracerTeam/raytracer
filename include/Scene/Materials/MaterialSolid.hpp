/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialSolid.hpp
*/

#pragma once

#include "IMaterial.hpp"

namespace Raytracer {
    class MaterialSolid : public IMaterial {
    public:
        MaterialSolid(const Color &color);
        ~MaterialSolid() = default;

        Color getColor(const RayHit &rayhit) override;

    private:
        Color m_color;
    };
} // namespace Raytracer
