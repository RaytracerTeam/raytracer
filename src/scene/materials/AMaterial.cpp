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
           // Math::Vector3D n = rayhit.getNormal();
        // const Math::Vector3D &l = lightDir;
        // const Math::Vector3D &u = ray.getDirection();
        // if (l.dot(n) <= 0.001)
        //     return Color();

        // Math::Vector3D r = (u - n * (2 * (n.dot(u)))).normalize(); // (n * 2. * (n.dot(l))) - l;
        // return light->getColor() * (std::pow(l.dot(r), 0.8));
    Color AMaterial::getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const
    {
        Math::Vector3D n = rayhit.getNormal();
        const Math::Vector3D &l = lightVec;
        if (l.dot(n) <= 0.001)
            return Color();

        Math::Vector3D r = (n * 2. * (n.dot(l))) - l;
        return light->getColor() * (std::pow(l.dot(r), 30));
    }
} // namespace Raytracer
