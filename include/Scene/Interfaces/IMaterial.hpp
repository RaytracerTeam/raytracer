/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IMaterial.hpp
*/

#pragma once

#include "Color.hpp"
#include "Scene/Ray.hpp"

namespace Raytracer {
    enum MaterialType {
        SOLID,
        CODE, // algorithm
        TEXTURE
    };

    class IMaterial {
    public:
        virtual Color getColor(const RayHit &rayhit) = 0;
    };
} // namespace Material
