/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** /!\ When the color is determined by a function.
*/

#pragma once

#include "IMaterial.hpp"

namespace Raytracer {
    class MaterialCode : public IMaterial {
    public:
        MaterialCode(const Color (&colorCode)(const RayHit &));
        ~MaterialCode() = default;

        Color getColor(const RayHit &rayhit) override;

    private:
        Color (&m_colorCode)(const RayHit &);
    };
} // namespace Raytracer
