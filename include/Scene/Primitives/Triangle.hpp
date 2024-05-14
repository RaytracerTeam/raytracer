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
        Triangle(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material,
        const Math::Vector3D &v1, const Math::Vector3D &v2, bool isPartOfObj = false)
            : APrimitive(origin, std::move(material))
            , m_v1(v1)
            , m_v2(v2)
            , m_isPartOfObj(isPartOfObj)
        {
        }
        ~Triangle() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::TRIANGLE; };

        const Math::Vector3D &getVec1() const { return m_v1; }
        const Math::Vector3D &getVec2() const { return m_v2; }
        bool isPartOfObj() const { return m_isPartOfObj; }
        void setIsPartOfObj(bool isPartOfObj) { m_isPartOfObj = isPartOfObj; }

        void setVec1(const Math::Vector3D &v1) { m_v1 = v1; }
        void setVec2(const Math::Vector3D &v2) { m_v2 = v2; }

        BoundingBox getBoundingBox(void) const override;
        std::optional<RayHit> hit(const Ray &ray) const override;

        Math::Vector3D getBarycentricCoordinates(const Math::Vector3D &point) const;

    private:
        Math::Vector3D m_v1;
        Math::Vector3D m_v2;
        bool m_isPartOfObj = false;
    };
} // namespace Raytracer
