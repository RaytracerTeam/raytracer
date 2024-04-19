/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"

#include <limits>

namespace Raytracer {
    class Ray {
    public:
        Ray(const Math::Vector3D &origin, const Math::Vector3D &direction);
        ~Ray() = default;

        Math::Vector3D getOrigin(void) const { return m_origin; }
        Math::Vector3D getDirection(void) const { return m_direction; }
    private:
        Math::Vector3D m_origin = Math::Vector3D(0, 0, 0);
        Math::Vector3D m_direction = Math::Vector3D(0, 0, 0);
    };

    class RayHit {
        public:
            RayHit() = default;
            ~RayHit() = default;

            RayHit(double distance, Math::Vector3D hitPt, Math::Vector3D normal);
            RayHit(const RayHit &rhit);
            RayHit &operator=(const RayHit &ray);

            bool isHit(void) const { return m_hit; }
            double getDistance(void) const { return m_distance; }
            Math::Vector3D getHitPoint(void) const { return m_hitPt; }
            Math::Vector3D getNormal(void) const { return m_normal; }

        private:
            bool m_hit = false;
            double m_distance = std::numeric_limits<double>::infinity();
            Math::Vector3D m_hitPt;
            Math::Vector3D m_normal;
    };
} // namespace Raytracer
