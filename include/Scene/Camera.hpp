/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Camera.hpp
*/

#pragma once

#include "Math/Angle3D.hpp"
#include "Math/Vector3D.hpp"
#include "Pixels.hpp"

#include <stddef.h>

namespace Raytracer {
    class Camera {
    public:
        Camera();
        Camera(Math::Vector3D pos, Math::Angle3D angle, const Dimension &dimension, double fov);
        Camera(const Dimension &dimension, double fov);
        ~Camera() = default;
        Camera &operator=(const Camera &ray);
        void reset(void) { m_pos = m_defaultPos; m_angle = m_defaultAngle; }

        const Dimension &getDimension(void) const { return m_dimension; }
        double getFov(void) const { return m_fov; }
        Math::Angle3D getAngle(void) const { return m_angle; }
        Math::Vector3D getPos(void) const { return m_pos; }
        Math::Vector3D getDefaultPos(void) const { return m_defaultPos; }
        Math::Angle3D getDefaultAngle(void) const { return m_defaultAngle; }

        void setDimension(const Dimension &a) { m_dimension = a; }
        void setFov(const double &a) { m_fov = a; }
        void setAngle(const Math::Angle3D &a) { m_angle = a; }
        void setDefaultAngle(const Math::Angle3D &a) { m_defaultAngle = a; }
        void setPos(const Math::Vector3D &a) { m_pos = a; }
        void setDefaultPos(const Math::Vector3D &a) { m_defaultPos = a; }
    private:
        Math::Vector3D m_pos;
        Math::Vector3D m_defaultPos;
        Math::Angle3D m_angle;
        Math::Angle3D m_defaultAngle;
        Dimension m_dimension;
        double m_fov;
    };
} // namespace Raytracer
