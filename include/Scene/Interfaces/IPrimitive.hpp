/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IPrimitive.h
*/

#pragma once

#include "IMaterial.hpp"
#include "ISceneObj.hpp"
#include "Scene/Ray.hpp"

#include <memory>
#include <optional>

namespace Raytracer {
    class IPrimitive : public ISceneObj {
    public:
        virtual void setMaterial(std::unique_ptr<IMaterial> material) = 0;
        virtual IMaterial *getMaterial(void) const = 0;

        virtual std::optional<RayHit> hit(const Ray &ray) const = 0;
    };
}
