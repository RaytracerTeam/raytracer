/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IPrimitive.h
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Math/Angle3D.hpp"

#include "Ray.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual void setOrigin(const Math::Vector3D &v) = 0;
            virtual void setAngle(const Math::Angle3D &v) = 0;

            // virtual void setSolidColor(const Math::Angle3D &v) = 0;

            // virtual Color getColor(const RayHit &rayhit) = 0;
            virtual RayHit hit(const Ray &ray) = 0;
    };
}
