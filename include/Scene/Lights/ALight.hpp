/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** ALight.hpp
*/

#pragma once

#include "Interfaces/ILight.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class ALight : public ILight {
    public:
        Color getColor(void) const override { return m_color; }
        const Math::Vector3D &getOrigin(void) const override { return m_origin; }

        void setTMatrix(const Math::Matrix44 &mat) override { m_mat = mat; };
        const Math::Matrix44 &getTMatrix(void) const override { return m_mat; };

        void setColor(const Color &color) override { m_color = color; }
        void setOrigin(const Math::Vector3D &origin) override { m_origin = origin; }

    protected:
        ALight(const Math::Vector3D &origin): m_origin(origin) {}
        ~ALight() = default;

        Math::Vector3D m_origin;
        Math::Matrix44 m_mat;
        Color m_color = Color(255U, 255U, 255U);
    };
} // namespace Raytracer
