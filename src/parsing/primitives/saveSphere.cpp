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
    void Parsing::saveSphere(libconfig::Setting &list, Sphere *sphere)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, sphere->getOrigin());

        libconfig::Setting &sphereRadius = setting.add(CFG_RADIUS, libconfig::Setting::TypeFloat);
        sphereRadius = sphere->getRadius();

        saveMaterial(setting, sphere);
        saveTransformations(setting, sphere);
    }
} // namespace Raytracer
