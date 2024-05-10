/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IMaterial.hpp
*/

#pragma once

#include "Color.hpp"
#include "Scene/Interfaces/ILight.hpp"
#include "Scene/Ray.hpp"

#include <optional>

namespace Raytracer {
    enum class MaterialType {
        SOLID,
        CODE, // algorithm
        TEXTURE,
        CHECKERBOARD,
        NONE
    };
    char const *const MaterialTypeStrings[] = {
        "Solid",
        "Code",
        "Texture",
        "Checkerboard",
        "None"
    };

    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        virtual MaterialType getType(void) const = 0;
        virtual const std::string getTypeString(void) const = 0;

        virtual double getAlbedo(void) const = 0;
        virtual bool hasPhong(void) const = 0;
        virtual double getTransparency(void) const = 0;
        virtual double getRefraction(void) const = 0;
        virtual double getFuzzFactor(void) const = 0;
        virtual double getEmission(void) const = 0;

        virtual void setAlbedo(double albedo) = 0;
        virtual void setHasPhong(bool hasPhong) = 0;
        virtual void setTransparency(double transparency) = 0;
        virtual void setRefraction(double refraction) = 0;
        virtual void setFuzzFactor(double fuzz) = 0;
        virtual void setEmission(double emission) = 0;

        virtual Color getColor(const RayHit &rayhit) const = 0;
        virtual Color getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const = 0;
        virtual std::optional<Ray> getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const = 0;
        virtual std::optional<Ray> getTransparencyRefractionRay(const Ray &rayIn, const RayHit &rayHit) const = 0;
        virtual std::optional<Ray> getTransparencyRay(const Ray &rayIn, const RayHit &rayHit) const = 0;

    };
} // namespace Raytracer
