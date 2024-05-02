/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** AMaterial.hpp
*/

#pragma once

#include "Scene/Interfaces/IMaterial.hpp"


namespace Raytracer {
    class AMaterial : public IMaterial {
        public:
            double getAlbedo(void) const override { return m_albedo; }
            double getEmission(void) const override { return m_emission; }
            double getFuzzFactor(void) const override { return m_fuzz; }

            void setAlbedo(double albedo) override { m_albedo = albedo; }
            void setEmission(double emission) override { m_emission = emission; }
            void setFuzzFactor(double fuzz) override { m_fuzz = fuzz; }

            Color getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const override;
            virtual std::optional<Ray> getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const override;
        protected:
            AMaterial() = default;
            ~AMaterial() = default;

            double m_albedo = 0; // 1 = mirror, 0 = opaque
            double m_emission = 0;
            double m_fuzz = 0;
    };
} // namespace Raytracer
