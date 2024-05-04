/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Camera.cpp
*/

#include "Scene/Camera.hpp"

namespace Raytracer {
    Camera::Camera()
        : m_pos(Math::Vector3D(0, 0, 0))
        , m_defaultPos(Math::Vector3D(0, 0, 0))
        , m_angle(Math::Angle3D(0, 0, 0))
        , m_defaultAngle(Math::Angle3D(0, 0, 0))
        , m_dimension(Dimension(640, 360))
        , m_fov(51.82)
    {
    }

    Camera::Camera(Math::Vector3D pos, Math::Angle3D angle, const Dimension &dimension, double fov)
        : m_pos(pos)
        , m_defaultPos(pos)
        , m_angle(angle)
        , m_defaultAngle(angle)
        , m_dimension(dimension)
        , m_fov(fov)
    {
    }

    Camera::Camera(const Dimension &dimension, double fov)
        : m_dimension(dimension)
        , m_fov(fov)
    {
    }

    Camera &Camera::operator=(const Camera &camera)
    {
        m_pos = camera.m_pos;
        m_defaultPos = camera.m_defaultPos;
        m_angle = camera.m_angle;
        m_defaultAngle = camera.m_defaultAngle;
        m_dimension = camera.m_dimension;
        m_fov = camera.m_fov;
        return *this;
    }

} // namespace Raytracer
