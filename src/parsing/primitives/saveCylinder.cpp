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
    void Parsing::saveCylinder(const Scene &scene, libconfig::Setting &list, Cylinder *cylinder)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        libconfig::Setting &pos = setting.add("position", libconfig::Setting::TypeGroup);
        pos.add("x", libconfig::Setting::TypeFloat) = cylinder->getOrigin().getX();
        pos.add("y", libconfig::Setting::TypeFloat) = cylinder->getOrigin().getY();
        pos.add("z", libconfig::Setting::TypeFloat) = cylinder->getOrigin().getZ();

        libconfig::Setting &radius = setting.add("radius", libconfig::Setting::TypeFloat);
        radius = cylinder->getRadius();

        libconfig::Setting &height = setting.add("height", libconfig::Setting::TypeFloat);
        height = cylinder->getHeight();

        // todo Only works with MaterialSolid
        libconfig::Setting &color = setting.add("color", libconfig::Setting::TypeGroup);
        MaterialSolid *material = dynamic_cast<MaterialSolid *>(cylinder->getMaterial());
        if (material) {
            color.add("r", libconfig::Setting::TypeInt) = (int)(material->getColor().getR() * 255);
            color.add("g", libconfig::Setting::TypeInt) = (int)(material->getColor().getG() * 255);
            color.add("b", libconfig::Setting::TypeInt) = (int)(material->getColor().getB() * 255);
        }
    }
} // namespace Raytracer
