/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IPrimitive.h
*/

#pragma once

#include "IMaterial.hpp"
#include "IShape.hpp"
#include "Optimisation/BoundingBox.hpp"
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
        TORUS,
        TANGLECUBE,
        MOBIUSSTRIP,
        OBJ,
        NONE
    };
    char const *const PrimitiveTypeStrings[] = {
        "Sphere",
        "Plane",
        "Triangle",
        "Cube",
        "Cylinder",
        "Cone",
        "Torus",
        "Tanglecube",
        "MobiusStrip",
        "Obj",
        "None"
    };
    class IPrimitive : public IShape {
    public:
        virtual void setMaterial(std::unique_ptr<IMaterial> material) = 0;
        virtual std::unique_ptr<IMaterial> &getMaterial(void) = 0;
        virtual const std::unique_ptr<IMaterial> &getMaterial(void) const = 0;

        virtual BoundingBox getBoundingBox(void) const = 0;

        virtual PrimitiveType getType(void) const = 0;
        virtual const std::string getTypeString(void) const = 0;

        virtual std::optional<RayHit> hit(const Ray &ray) const = 0;

        virtual void setRotXYZ(double rotX, double rotY, double rotZ) = 0;
        virtual const Math::Matrix44 &getTMatrix(void) const = 0;
    };
}
