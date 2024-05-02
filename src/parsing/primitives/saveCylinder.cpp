/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveCylinder
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Cylinder.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveCylinder(libconfig::Setting &list, Cylinder *cylinder)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, cylinder);

        libconfig::Setting &radius = setting.add("radius", libconfig::Setting::TypeFloat);
        radius = cylinder->getRadius();

        libconfig::Setting &height = setting.add("height", libconfig::Setting::TypeFloat);
        height = cylinder->getHeight();

        saveColor(setting, cylinder);
    }
} // namespace Raytracer
