/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** CameraTexture
*/

#pragma once

#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"

namespace Raytracer {
    class CameraTexture : public SphereTexture {
    public:
        MaterialType getType() const override { return MaterialType::CAMERA; }
    };
} // namespace Raytracer
