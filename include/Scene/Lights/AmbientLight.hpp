/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** AmbientLight.hpp
*/

#pragma once

#include "ALight.hpp"

namespace Raytracer {
    class AmbientLight : public ALight {
    public:
        AmbientLight(const Color &color = {255U, 0, 255}, double intensity = 1.)
            : ALight(color, intensity)
        {
        }

        LightType getType(void) const override { return LightType::AMBIENT; }
    private:
    };
}
