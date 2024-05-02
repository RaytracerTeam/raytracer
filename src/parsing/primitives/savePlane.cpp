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
    void Parsing::savePlane(const Scene &scene, libconfig::Setting &planeList, Plane *plane)
    {
        libconfig::Setting &planeSetting = planeList.add(libconfig::Setting::TypeGroup);

        libconfig::Setting &planeNormal = planeSetting.add("axis", libconfig::Setting::TypeString);
        planeNormal = plane->getAxisString();

        libconfig::Setting &planePos = planeSetting.add("position", libconfig::Setting::TypeFloat);
        Plane::Axis axis = plane->getAxis();
        planePos = plane->getPos();

        saveColor(planeSetting, plane);
    }
} // namespace Raytracer
