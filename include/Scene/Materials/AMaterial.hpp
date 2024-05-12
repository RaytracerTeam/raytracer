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

            double getReflection(void) const override { return m_reflection; }
            double getTransparency(void) const override { return m_transparency; }
            double getRefraction(void) const override { return m_refractionIndex; }
            float getDiffuse(void) const override { return m_diffuse; }
            float getSpecular(void) const override { return m_specular; }
            float getShininess(void) const override { return m_shininess; }

            void setReflection(double reflection) override { m_reflection = reflection; }
            void setTransparency(double transparency) override { m_transparency = transparency; }
            void setRefraction(double refraction) override { m_refractionIndex = refraction; }
            void setDiffuse(float diffuse) override { m_diffuse = diffuse; }
            void setSpecular(float specular) override { m_specular = specular; }
            void setShininess(float shininess) override { m_shininess = shininess; }

            Color getSpecular(const ILight *light, Math::Vector3D surfaceNormal,
                const Math::Vector3D &lightVec, const Ray &ray) const override;
            virtual std::optional<Ray> getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const override;
            virtual std::optional<Ray> getTransparencyRefractionRay(const Ray &rayIn, const RayHit &rayHit) const override;
            virtual std::optional<Ray> getTransparencyRay(const Ray &rayIn, const RayHit &rayHit) const override;
            #ifdef BONUSCAMERA
            void setIsCamera(bool isCamera) override { m_isCamera = isCamera; }
            bool isCamera(void) const override { return m_isCamera; }
            #endif
        protected:
            AMaterial() = default;
            ~AMaterial() = default;

            double m_reflection = 0; // 1 = mirror, 0 = opaque
            double m_transparency = 0;
            double m_refractionIndex = 1.3; // Water refraction

            float m_diffuse = 0.9;
            float m_specular = 0.0;
            float m_shininess = 10.0;

            #ifdef BONUSCAMERA
            bool m_isCamera = false;
            #endif
    };
} // namespace Raytracer
