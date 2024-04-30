/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IMaterial.hpp
*/

#pragma once

#include "Color.hpp"
#include "Scene/Interfaces/ILight.hpp"
#include "Scene/Ray.hpp"

namespace Raytracer {
    enum MaterialType {
        SOLID,
        CODE, // algorithm
        TEXTURE
    };

    class IMaterial {
    public:
        virtual Color getColor(const RayHit &rayhit) const = 0;
        virtual Color getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const = 0;
    };
} // namespace Material
