/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.h
*/

#pragma once

#include "IPrimitive.hpp"

namespace Raytracer {
    class APrimitive : public IPrimitive {
        public:
            virtual void setOrigin(Math::Vector3D &v) override {
                m_origin = v;
            }
            virtual void setAngle(Math::Angle3D &a) override {
                m_angle = a;
            }
            virtual bool hit(Ray &ray) = 0;
        protected:
            APrimitive() = default;
            ~APrimitive() = default;

            Math::Angle3D m_angle;
            Math::Vector3D m_origin;
    };
} // namespace Raytracer
