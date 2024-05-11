/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SphereTexture.hpp
*/

#pragma once

#include "Scene/Materials/MaterialTexture.hpp"

namespace Raytracer {
    class SphereTexture : public MaterialTexture {
    public:
        SphereTexture() = default;
        SphereTexture(const std::string &pathname);
        ~SphereTexture() = default;

        Color getColor(const RayHit &rayhit) const override;
        Color getColor(double u, double v) const override final;
    };
} // namespace Raytracer
