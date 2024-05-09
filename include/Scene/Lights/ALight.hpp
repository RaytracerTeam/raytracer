/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** ALight.hpp
*/

#pragma once

#include "Scene/Interfaces/ILight.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class ALight : public ILight {
    public:
        LightType getType(void) const override { return LightType::NONE; };
        const std::string getTypeString(void) const override { return LightTypeStrings[static_cast<int>(getType())]; };

        Color getColor(void) const override { return m_color; }
        void setColor(const Color &color) override { m_color = color; }

        double getIntensity(void) const override { return m_intensity; }
        void setIntensity(double intensity) override { m_intensity = intensity; }

    protected:
        ALight(const Color &color = {255U, 255U, 255U}, double intensity = 1.)
            : m_color(color)
            , m_intensity(intensity)
        {
        }
        ~ALight() = default;

        Color m_color;
        double m_intensity;
    };
} // namespace Raytracer
