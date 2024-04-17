/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Ray {
    public:
        Ray(const Math::Point3D &origin, const Math::Vector3D &direction);
        ~Ray() = default;

        Math::Point3D getOrigin(void) const { return m_origin; }
        Math::Vector3D getDirection(void) const { return m_direction; }
    private:
        Math::Point3D m_origin = Math::Vector3D(0., 0., 0.);
        Math::Vector3D m_direction = Math::Vector3D(0., 0., 0.);
    };

    class RayHit {
        public:
            RayHit() = default;
            RayHit(bool hit, double distance, Math::Point3D m_hitPt, Math::Vector3D m_normal);
            ~RayHit() = default;
        private:
            bool m_hit = false;
            double m_distance = 0.;
            Math::Point3D m_hitPt;
            Math::Vector3D m_normal;
    };
} // namespace Raytracer
