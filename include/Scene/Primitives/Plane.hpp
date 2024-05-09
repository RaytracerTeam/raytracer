/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Plane.hpp
*/

#pragma once

#include "APrimitive.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Plane : public APrimitive {
    public:
        enum Axis {
            X,
            Y,
            Z
        };
        Plane(const Math::Vector3D &origin,  std::unique_ptr<IMaterial> material);
        Plane(double pos, std::unique_ptr<IMaterial> material, const Axis &axis);
        ~Plane() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::PLANE; };

        float getPos(void) const { return m_pos; }
        void setPos(float pos) { m_pos = pos; setOrigin(Math::Vector3D(pos, pos, pos)); }
        // todo Either add switch to keep infinity or remove infinity

        BoundingBox getBoundingBox(void) const override;
        std::optional<RayHit> hit(const Ray &ray) const override;

        Axis getAxis(void) const { return m_axis; }
        std::string getAxisString(void) const;

        void setAxis(const Axis &axis) { m_axis = axis; }
    private:
        Math::Vector3D getNormal(void) const;
        float m_pos = 0;
        Axis m_axis = Z;
    };
} // namespace Raytracer
