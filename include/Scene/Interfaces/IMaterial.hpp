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
        TEXTURE_SPHERE,
        TEXTURE_TRIANGLE,
        TEXTURE_PLANE,
        NONE
    };
    char const *const MaterialTypeStrings[] = {
        "Solid",
        "Code",
        "Texture",
        "TextureSphere",
        "TextureTriangle",
        "TexturePlane",
        "Checkerboard",
        "None"
    };

    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        virtual MaterialType getType(void) const = 0;
        virtual const std::string getTypeString(void) const = 0;

        virtual double getReflection(void) const = 0;
        virtual double getTransparency(void) const = 0;
        virtual double getRefraction(void) const = 0;
        virtual float getDiffuse(void) const = 0;
        virtual float getSpecular(void) const = 0;
        virtual float getShininess(void) const = 0;

        virtual void setReflection(double reflection) = 0;
        virtual void setTransparency(double transparency) = 0;
        virtual void setRefraction(double refraction) = 0;
        virtual void setDiffuse(float diffuse) = 0;
        virtual void setSpecular(float specular) = 0;
        virtual void setShininess(float shininess) = 0;

        virtual Color getColor(const RayHit &rayhit) const = 0;
        virtual Color getSpecular(const ILight *light, Math::Vector3D surfaceNormal,
            const Math::Vector3D &lightVec, const Ray &ray) const = 0;
        virtual std::optional<Ray> getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const = 0;
        virtual std::optional<Ray> getTransparencyRefractionRay(const Ray &rayIn, const RayHit &rayHit) const = 0;
        virtual std::optional<Ray> getTransparencyRay(const Ray &rayIn, const RayHit &rayHit) const = 0;

        #ifdef BONUSCAMERA
        virtual void setIsCamera(bool isCamera) = 0;
        virtual bool isCamera(void) const = 0;
        #endif
    };
} // namespace Raytracer
