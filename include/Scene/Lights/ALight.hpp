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

        bool isShown(void) const override { return m_isShown; }
        void setIsShown(bool isShown) override { m_isShown = isShown; }
        bool getDieASAP(void) const override { return m_dieASAP; }
        void setDieASAP(bool dieASAP) override { m_dieASAP = dieASAP; }
        void dieASAP(void) override { m_dieASAP = true; }

    protected:
        ALight(const Color &color = {255U, 255U, 255U}, double intensity = 1.)
            : m_color(color)
            , m_intensity(intensity)
        {
        }
        ~ALight() = default;

        Color m_color;
        double m_intensity;
        bool m_isShown = true;
        bool m_dieASAP = false;
    };
} // namespace Raytracer
