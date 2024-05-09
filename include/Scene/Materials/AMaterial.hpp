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
            MaterialType getType(void) const override { return MaterialType::NONE; };
            const std::string getTypeString(void) const override { return MaterialTypeStrings[static_cast<int>(getType())]; };

            double getAlbedo(void) const override { return m_albedo; }
            double getEmission(void) const override { return m_emission; }
            double getFuzzFactor(void) const override { return m_fuzz; }
            double getTransparency(void) const override { return m_transparency; }
            bool hasPhong(void) const override { return m_hasPhong; }
            bool hasReflection(void) const override { return m_hasReflection; }

            void setAlbedo(double albedo) override { m_albedo = albedo; }
            void setEmission(double emission) override { m_emission = emission; }
            void setFuzzFactor(double fuzz) override { m_fuzz = fuzz; }
            void setTransparency(double transparency) override { m_transparency = transparency; }
            void setHasPhong(bool hasPhong) override { m_hasPhong = hasPhong; }
            void setHasReflection(bool hasReflection) override { m_hasReflection = hasReflection; }

            Color getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const override;
            virtual std::optional<Ray> getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const override;
            virtual std::optional<Ray> getTransparencyReflectionRay(const Ray &rayIn, const RayHit &rayHit) const override;
            virtual std::optional<Ray> getTransparencyRay(const Ray &rayIn, const RayHit &rayHit) const override;
        protected:
            AMaterial() = default;
            ~AMaterial() = default;

            double m_albedo = 0; // 1 = mirror, 0 = opaque
            double m_emission = 0;
            double m_fuzz = 0;
            double m_transparency = 0;
            bool m_hasPhong = false;
            bool m_hasReflection = true;
    };
} // namespace Raytracer
