/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Math/Matrix44d.hpp"

#include <limits>
#include <vector>

namespace Raytracer {
    class Ray {
    public:
        Ray(const Math::Vector3D &origin, const Math::Vector3D &direction, size_t depth = 0);
        ~Ray() = default;

        Math::Vector3D getOrigin(void) const { return m_origin; }
        Math::Vector3D getDirection(void) const { return m_direction; }
        size_t getDepth(void) const { return m_depth; }

    private:
        Math::Vector3D m_origin = Math::Vector3D(0, 0, 0);
        Math::Vector3D m_direction = Math::Vector3D(0, 0, 0);
        size_t m_depth;
    };

    class RayHit {
        public:
            RayHit() = default;
            ~RayHit() = default;

            RayHit(double distance, Math::Vector3D hitPt, Math::Vector3D normal,
                Math::Vector3D relativeHitPt = Math::Vector3D(0, 0, 0));
            RayHit(const RayHit &rhit);
            RayHit &operator=(const RayHit &ray);

            void setRelativeHitPoint(Math::Vector3D relativeHitPt) { m_relativeHitPt = relativeHitPt; }

            double getDistance(void) const { return m_distance; }
            Math::Vector3D getHitPoint(void) const { return m_hitPt; }
            Math::Vector3D getRelativeHitPoint(void) const { return m_relativeHitPt; }
            Math::Vector3D getNormal(void) const { return m_normal; }

        private:
            double m_distance = std::numeric_limits<double>::infinity();
            Math::Vector3D m_hitPt;
            Math::Vector3D m_relativeHitPt;
            Math::Vector3D m_normal;
    };
} // namespace Raytracer
