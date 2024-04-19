/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** /!\ When the color is determined by a function.
*/

#pragma once

#include "AMaterial.hpp"

namespace Raytracer {
    class MaterialCode : public AMaterial {
    public:
        MaterialCode(Color (&colorCode)(const RayHit &));
        ~MaterialCode() = default;

        Color getColor(const RayHit &rayhit) const override;

    private:
        Color (*m_colorCode)(const RayHit &);
    };
} // namespace Raytracer
