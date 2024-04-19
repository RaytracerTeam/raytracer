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
    Color AMaterial::getSpecular(const ILight *light, const RayHit &rayhit) const
    {
        Math::Vector3D n = rayhit.getNormal();
        Math::Vector3D l = light->getOrigin();
        Math::Vector3D r = (n * 2. * (n.dot(l))) - l;

        return light->getColor() * (std::pow(l.dot(r), light->getDiffuse()));
    }
} // namespace Raytracer
