/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** AMaterial.cpp
*/

#include "Scene/Materials/AMaterial.hpp"

#include <cmath>

namespace Raytracer {
    /*
    calculates specular composant
    Admits we have clear view of light
    https://euler.ac-versailles.fr/IMG/pdf/raytracing.pdf
    */
    Color AMaterial::getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const
    {
        Math::Vector3D n = rayhit.getNormal();
        const Math::Vector3D &l = lightVec;
        if (l.dot(n) <= 0.001)
            return Color();

        Math::Vector3D r = (n * 2. * (n.dot(l))) - l;
        return light->getColor() * (std::pow(l.dot(r), 30));
    }

    // todo : add fuzzing that makes reflections go random direction
    std::optional<Ray> AMaterial::getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const
    {
        Math::Vector3D reflected = Math::Vector3D::gReflect(rayIn.getDirection().normalize(), rayHit.getNormal());
        Ray rayScattered = Ray(rayHit.getHitPoint(), reflected, rayIn.getDepth() + 1);

        if (rayScattered.getDirection().dot(rayHit.getNormal()) <= 0.001)
            return std::nullopt;
        return rayScattered;
    }
} // namespace Raytracer
