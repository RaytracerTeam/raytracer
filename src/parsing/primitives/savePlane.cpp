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

        libconfig::Setting &planeColor = planeSetting.add("color", libconfig::Setting::TypeGroup);
        MaterialSolid *material = dynamic_cast<MaterialSolid *>(plane->getMaterial());
        if (material) {
            planeColor.add("r", libconfig::Setting::TypeInt) = (int)material->getColor().getR() * 255;
            planeColor.add("g", libconfig::Setting::TypeInt) = (int)material->getColor().getG() * 255;
            planeColor.add("b", libconfig::Setting::TypeInt) = (int)material->getColor().getB() * 255;
        }
    }
} // namespace Raytracer
