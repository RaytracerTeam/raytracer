/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** AMaterial.hpp
*/

#pragma once

#include "Scene/Interfaces/IMaterial.hpp"
#include "Scene/Scene.hpp"


namespace Raytracer {
    class AMaterial : public IMaterial {
        public:
            double getAlbedo(void) const { return m_albedo; }
            double getEmission(void) const { return m_emission; }

            void setAlbedo(double albedo) { m_albedo = albedo; }
            void setEmission(double emission) { m_emission = emission; }

            Color getSpecular(const ILight *light, const RayHit &rayhit) const override;
        protected:
            AMaterial() = default;
            ~AMaterial() = default;

            double m_albedo; // 1 = mirror, 0 = opaque
            double m_emission;
    };
} // namespace Raytracer
