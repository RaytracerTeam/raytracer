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
#include "Math/MatrixT.hpp"

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
        NONE,
        SIZE
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
        "None",
        "Size"
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

        virtual void setTranslation(const Math::Vector3D &translation) = 0;
        virtual void setRotation(const Math::Vector3D &rotation) = 0;
        virtual void setScale(const Math::Vector3D &scale) = 0;

        virtual const Math::MatrixT &getMatrixT(void) const = 0;
        virtual const Math::Vector3D &getTranslation(void) const = 0;
        virtual const Math::Vector3D &getRotation(void) const = 0;
        virtual const Math::Vector3D &getScale(void) const = 0;

        virtual void updateTransformations(void) = 0;
    };
}
