/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** TriangleTexture.hpp
*/

#pragma once

#include "Scene/Materials/MaterialTexture.hpp"

namespace Raytracer {
    class TriangleTexture : public MaterialTexture {
    public:
        TriangleTexture() = default;
        TriangleTexture(const std::string &pathname) : MaterialTexture(pathname) {
            m_area2 = 1;
        }
        TriangleTexture(std::shared_ptr<sf::Image> image) : MaterialTexture(image) {
            m_area2 = 1;
        }
        TriangleTexture(std::shared_ptr<sf::Image> image, Math::Vector3D VT1, Math::Vector3D VT2, Math::Vector3D VT3)
            : MaterialTexture(image), m_vt1(VT1), m_vt2(VT2), m_vt3(VT3) {
                m_area2 = (m_vt2 - m_vt1).cross(m_vt3 - m_vt1).length();
            }
        ~TriangleTexture() = default;

        MaterialType getType() const override { return MaterialType::TRIANGLE; }

        Math::Vector3D getVT1() const { return m_vt1; }
        Math::Vector3D getVT2() const { return m_vt2; }
        Math::Vector3D getVT3() const { return m_vt3; }

        void setVT1(const Math::Vector3D &vt1) { m_vt1 = vt1; }
        void setVT2(const Math::Vector3D &vt2) { m_vt2 = vt2; }
        void setVT3(const Math::Vector3D &vt3) { m_vt3 = vt3; }

        Color getColor(const RayHit &rayhit) const override final;
        Color getColor(double u, double v) const override final;
    private:
        Math::Vector3D m_vt1 = Math::Vector3D(0, 0, 0);
        Math::Vector3D m_vt2 = Math::Vector3D(0, 1, 0);
        Math::Vector3D m_vt3 = Math::Vector3D(1, 0, 0);
        float m_area2 = 0;
    };
} // namespace Raytracer
