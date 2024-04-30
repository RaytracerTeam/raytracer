/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveSphere
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Sphere.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveSphere(const Scene &scene, libconfig::Setting &sphereList, Sphere *sphere)
    {
        libconfig::Setting &sphereSetting = sphereList.add(libconfig::Setting::TypeGroup);

        savePos(sphereSetting, sphere);

        libconfig::Setting &sphereRadius = sphereSetting.add("radius", libconfig::Setting::TypeFloat);
        sphereRadius = sphere->getRadius();

        saveColor(sphereSetting, sphere);
    }
} // namespace Raytracer
