/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BoundingBox.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Scene/Ray.hpp"

namespace Raytracer {
    class BoundingBox {
    public:
        BoundingBox(const Math::Vector3D &min_, const Math::Vector3D &max_)
            : min(min_)
            , max(max_)
        {
        }
        ~BoundingBox() = default;

        bool intersect(const Ray &ray) const;
        double surfaceArea(void) const;

        Math::Vector3D min;
        Math::Vector3D max;
    };
} // namespace Raytracer
