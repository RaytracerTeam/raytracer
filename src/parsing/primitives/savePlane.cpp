/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** savePlane
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Plane.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::savePlane(libconfig::Setting &list, Plane *plane)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        libconfig::Setting &planeNormal = setting.add("axis", libconfig::Setting::TypeString);
        planeNormal = plane->getAxisString();

        libconfig::Setting &planePos = setting.add(CFG_POSITION, libconfig::Setting::TypeFloat);
        planePos = plane->getPos();

        saveMaterial(setting, plane);
        saveTransformations(setting, plane);
    }
} // namespace Raytracer
