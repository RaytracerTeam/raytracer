/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cube.hpp
*/

#pragma once

#include "APrimitive.hpp"

namespace Raytracer {
    class Cube : public APrimitive {
    public:
        Cube(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material, const Math::Vector3D &v1)
            : APrimitive(origin, std::move(material))
            , m_v1(v1)
        {
        }
        ~Cube() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::CUBE; };

        const Math::Vector3D &getVec1() const { return m_v1; }

        void setVec1(const Math::Vector3D &v1) { m_v1 = v1; }

        BoundingBox getBoundingBox(void) const override;
        std::optional<RayHit> hit(const Ray &ray) const override;
        RayHit getNormal(double distance, const Math::Vector3D &hitPt, int hitFace) const;

    private:
        Math::Vector3D m_v1;
    };
} // namespace Raytracer
