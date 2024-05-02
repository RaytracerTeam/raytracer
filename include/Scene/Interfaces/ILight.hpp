/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** ILight.hpp
*/

#pragma once

#include "Color.hpp"
#include "ISceneObj.hpp"

namespace Raytracer {
    class ILight {
    public:
        virtual Color getColor(void) const = 0;
        virtual double getIntensity(void) const = 0;

        virtual void setColor(const Color &color) = 0;
        virtual void setIntensity(double intensity) = 0;
    };
} // namespace Material
