/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveCylinder
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Cylinder.hpp"

namespace Raytracer
{
    void Parsing::saveCylinder(libconfig::Setting &list, Cylinder *cylinder)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, cylinder->getOrigin());

        libconfig::Setting &radius = setting.add(CFG_RADIUS, libconfig::Setting::TypeFloat);
        radius = cylinder->getRadius();

        libconfig::Setting &height = setting.add(CFG_HEIGHT, libconfig::Setting::TypeFloat);
        height = cylinder->getHeight();

        saveMaterial(setting, cylinder->getMaterial());
        saveTransformations(setting, cylinder);
    }
} // namespace Raytracer
