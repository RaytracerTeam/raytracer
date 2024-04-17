/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Camera.hpp
*/

#pragma once

#include "Math/Angle3D.hpp"
#include "Math/Vector3D.hpp"

#include <stddef.h>

namespace Raytracer {
    typedef struct s_pixels {
        size_t width;
        size_t height;
    } pixels_t;

    typedef struct s_pixel {
        double x;
        double y;
    } pixel_t;

    class Camera {
    public:
        Camera(Math::Vector3D pos, Math::Angle3D angle, size_t width, size_t height, double fov)
            : m_pos(pos)
            , m_angle(angle)
            , m_dimension({ width, height })
            , m_fov(fov)
        {
        }
        Camera(size_t width, size_t height, double fov)
            : m_dimension({ width, height })
            , m_fov(fov)
        {
        }
        ~Camera() = default;

        pixels_t getDimension(void) const { return m_dimension; }
        double getFov(void) const { return m_fov; }
        Math::Angle3D getAngle(void) const { return m_angle; }
        Math::Vector3D getPos(void) const { return m_pos; }

    private:
        Math::Vector3D m_pos;
        Math::Angle3D m_angle;
        pixels_t m_dimension;
        double m_fov;
    };
} // namespace Raytracer
