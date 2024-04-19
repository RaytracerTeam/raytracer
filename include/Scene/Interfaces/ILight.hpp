/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** ILight.hpp
*/

#pragma once

#include "ISceneObj.hpp"
#include "Color.hpp"

namespace Raytracer {
    class ILight : public ISceneObj {
    public:
        virtual Color getColor(void) const = 0;
        virtual double getDiffuse(void) const = 0;

        virtual void setColor(const Color &color) = 0;
        virtual void setDiffuse(double diffuse) = 0;
    };
} // namespace Material
