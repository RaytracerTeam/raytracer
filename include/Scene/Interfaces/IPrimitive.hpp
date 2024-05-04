/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IPrimitive.h
*/

#pragma once

#include "IMaterial.hpp"
#include "ISceneObj.hpp"
#include "IShape.hpp"
#include "Scene/Ray.hpp"

#include <memory>
#include <optional>

namespace Raytracer {
    enum class PrimitiveType {
        SPHERE,
        PLANE,
        TRIANGLE,
        CUBE,
        CYLINDER,
        CONE,
        NONE
    };
    class IPrimitive : public IShape {
    public:
        virtual void setMaterial(std::unique_ptr<IMaterial> material) = 0;
        virtual IMaterial *getMaterial(void) const = 0;

        virtual PrimitiveType getType(void) const = 0;
        virtual const std::string getTypeString(void) const = 0;

        virtual std::optional<RayHit> hit(const Ray &ray) const = 0;
    };
}
