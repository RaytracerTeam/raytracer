/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** AShapeLight.hpp
*/

#pragma once

#include "Scene/Interfaces/IShape.hpp"
#include "Scene/Lights/ALight.hpp"

namespace Raytracer {
    class AShapeLight : public ALight, public IShape {
    public:
        int getID(void) const override { return m_id; }
        bool isShown(void) const override { return m_isShown; }
        Color getColor(void) const override { return m_color; }
        const Math::Vector3D &getOrigin(void) const override { return m_origin; }
        double getIntensity(void) const override { return m_intensity; }
        bool getDieASAP(void) const override { return m_dieASAP; }

        void setID(int id) override { m_id = id; }
        void setIsShown(bool isShown) override { m_isShown = isShown; }
        void setColor(const Color &color) override { m_color = color; }
        void setOrigin(const Math::Vector3D &origin) override { m_origin = origin; }
        void setIntensity(double intensity) override { m_intensity = intensity; }
        void setDieASAP(bool dieASAP) override { m_dieASAP = dieASAP; }

        void dieASAP(void) override { m_dieASAP = true; }

    protected:
        AShapeLight(const Math::Vector3D &origin, const Color &color = { 255U, 255U, 255U }, double intensity = 1.)
            : ALight(color, intensity)
            , m_origin(origin)
        {
        }
        ~AShapeLight() = default;

        int m_id = -1;
        Math::Vector3D m_origin;
        bool m_isShown = true;
        bool m_dieASAP = false;
    };
} // namespace Raytracer
