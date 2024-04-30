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
        Color getColor(void) const override { return m_color; }
        const Math::Vector3D &getOrigin(void) const override { return m_origin; }
        const Math::Matrix44 &getTMatrix(void) const override { return m_mat; };
        double getIntensity(void) const override { return m_intensity; }

        void setTMatrix(const Math::Matrix44 &mat) override { m_mat = mat; };
        void setColor(const Color &color) override { m_color = color; }
        void setOrigin(const Math::Vector3D &origin) override { m_origin = origin; }
        void setIntensity(double intensity) { m_intensity = intensity; }

    protected:
        AShapeLight(const Math::Vector3D &origin, const Color &color = { 255U, 255U, 255U }, double intensity = 1.)
            : ALight(color, intensity)
            , m_origin(origin)
        {
        }
        ~AShapeLight() = default;

        Math::Vector3D m_origin;
        Math::Matrix44 m_mat;
    };
} // namespace Raytracer
