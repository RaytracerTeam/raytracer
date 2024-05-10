/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** ISceneObj.hpp
*/

#pragma once

#include "Math/Matrix44d.hpp"
#include "Math/Vector3D.hpp"

namespace Raytracer {
    class ISceneObj {
    public:
        virtual ~ISceneObj() = default;
        virtual void setOrigin(const Math::Vector3D &origin) = 0;
        virtual const Math::Vector3D &getOrigin(void) const = 0;

        /* tranform matrix */
        virtual void setTMatrix(const Math::Matrix44 &mat) = 0;
        virtual void setTMatrix(double rotX, double rotY, double rotZ) = 0;
        virtual const Math::Matrix44 &getTMatrix(void) const = 0;
    };
} // namespace Raytracer
