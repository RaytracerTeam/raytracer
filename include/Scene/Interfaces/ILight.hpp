/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** ILight.hpp
*/

#pragma once

#include "Color.hpp"
#include "Math/Matrix44d.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {

    enum class LightType {
        AMBIENT,
        POINT,
        DIRECTIONAL,
        SPOT,
        NONE
    };
    char const *const LightTypeStrings[] = {
        "Ambient",
        "Point",
        "Directional",
        "Spot",
        "None"
    };
    class ILight {
    public:
        virtual ~ILight() = default;

        virtual LightType getType(void) const = 0;
        virtual const std::string getTypeString(void) const = 0;

        virtual Color getColor(void) const = 0;
        virtual double getIntensity(void) const = 0;

        virtual void setColor(const Color &color) = 0;
        virtual void setIntensity(double intensity) = 0;
    };
} // namespace Material
