/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveTorus
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Torus.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveTorus(libconfig::Setting &list, Torus *torus)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, torus->getOrigin());

        libconfig::Setting &radius = setting.add(CFG_RADIUS, libconfig::Setting::TypeFloat);
        radius = torus->getRadius();

        libconfig::Setting &height = setting.add(CFG_DISTANCE, libconfig::Setting::TypeFloat);
        height = torus->getDistance();

        saveMaterial(setting, torus);
        saveTransformations(setting, torus);
    }
} // namespace Raytracer
