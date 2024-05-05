/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Triangle.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Triangle : public APrimitive {
    public:
        Triangle(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material, const Math::Vector3D &v1, const Math::Vector3D &v2)
            : APrimitive(origin, std::move(material))
            , m_v1(v1)
            , m_v2(v2)
        {
        }
        ~Triangle() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::TRIANGLE; };
        const std::string getTypeString(void) const override { return "Triangle"; };

        const Math::Vector3D &getVec1() const { return m_v1; }
        const Math::Vector3D &getVec2() const { return m_v2; }

        void setVec1(const Math::Vector3D &v1) { m_v1 = v1; }
        void setVec2(const Math::Vector3D &v2) { m_v2 = v2; }

        std::optional<RayHit> hit(const Ray &ray) const override;

    private:
        Math::Vector3D m_v1;
        Math::Vector3D m_v2;
    };
} // namespace Raytracer
