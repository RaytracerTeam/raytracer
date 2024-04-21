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
        Color getColor(void) const override { return m_color; }
        const Math::Vector3D &getOrigin(void) const override { return m_origin; }
        double getDiffuse(void) const override { return m_diffuse; }

        void setTMatrix(const Math::Matrix44 &mat) override { m_mat = mat; };
        const Math::Matrix44 &getTMatrix(void) const override { return m_mat; };

        void setColor(const Color &color) override { m_color = color; }
        void setOrigin(const Math::Vector3D &origin) override { m_origin = origin; }
        void setDiffuse(double diffuse) override { m_diffuse = diffuse; }

    protected:
        ALight(const Math::Vector3D &origin, const Color &color = {255U, 255U, 255U}, double diffuse = 0)
            : m_origin(origin)
            , m_color(color)
            , m_diffuse(diffuse)
        {
        }
        ~ALight() = default;

        Math::Vector3D m_origin;
        Math::Matrix44 m_mat;
        Color m_color;
        double m_diffuse;
    };
} // namespace Raytracer
