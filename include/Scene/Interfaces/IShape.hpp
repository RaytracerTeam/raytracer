/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IShape.hpp
*/

#pragma once

#include "IMaterial.hpp"
#include "ISceneObj.hpp"
#include "Scene/Ray.hpp"

#include <memory>
#include <optional>

namespace Raytracer {
    class IShape : public ISceneObj {
    public:
        virtual std::optional<RayHit> hit(const Ray &ray) const = 0;
    };
}
