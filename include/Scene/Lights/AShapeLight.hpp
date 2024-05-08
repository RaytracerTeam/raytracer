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
        const Math::Matrix44 &getTMatrix(void) const override { return m_mat; };
        double getIntensity(void) const override { return m_intensity; }

        void setID(int id) override { m_id = id; }
        void setIsShown(bool isShown) override { m_isShown = isShown; }
        void setTMatrix(const Math::Matrix44 &mat) override { m_mat = mat; };
        void setTMatrix(double rotX, double rotY, double rotZ) override { m_mat = Math::Matrix44(rotX, rotY, rotZ); };
        void setColor(const Color &color) override { m_color = color; }
        void setOrigin(const Math::Vector3D &origin) override { m_origin = origin; }
        void setIntensity(double intensity) override { m_intensity = intensity; }

    protected:
        AShapeLight(const Math::Vector3D &origin, const Color &color = { 255U, 255U, 255U }, double intensity = 1.)
            : ALight(color, intensity)
            , m_origin(origin)
        {
        }
        ~AShapeLight() = default;

        Math::Vector3D m_origin;
        Math::Matrix44 m_mat;
        int m_id = -1;
        bool m_isShown = true;
    };
} // namespace Raytracer
