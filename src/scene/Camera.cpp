/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Camera.cpp
*/

#include "Scene/Camera.hpp"

namespace Raytracer {
    Camera::Camera(Math::Vector3D pos, Math::Angle3D angle, Dimension &dimension, double fov)
        : m_pos(pos)
        , m_angle(angle)
        , m_dimension(dimension)
        , m_fov(fov)
    {
    }

    Camera::Camera(Dimension &dimension, double fov)
        : m_dimension(dimension)
        , m_fov(fov)
    {
    }

    Camera &Camera::operator=(const Camera &camera)
    {
        m_pos = camera.m_pos;
        m_angle = camera.m_angle;
        m_dimension = camera.m_dimension;
        m_fov = camera.m_fov;
        return *this;
    }

} // namespace Raytracer
