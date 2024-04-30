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

        libconfig::Setting &spherePos = sphereSetting.add("position", libconfig::Setting::TypeGroup);
        spherePos.add("x", libconfig::Setting::TypeFloat) = sphere->getOrigin().getX();
        spherePos.add("y", libconfig::Setting::TypeFloat) = sphere->getOrigin().getY();
        spherePos.add("z", libconfig::Setting::TypeFloat) = sphere->getOrigin().getZ();

        libconfig::Setting &sphereRadius = sphereSetting.add("radius", libconfig::Setting::TypeFloat);
        sphereRadius = sphere->getRadius();

        // todo Only works with MaterialSolid
        libconfig::Setting &sphereColor = sphereSetting.add("color", libconfig::Setting::TypeGroup);
        MaterialSolid *material = dynamic_cast<MaterialSolid *>(sphere->getMaterial());
        if (material) {
            sphereColor.add("r", libconfig::Setting::TypeInt) = (int)(material->getColor().getR() * 255);
            sphereColor.add("g", libconfig::Setting::TypeInt) = (int)(material->getColor().getG() * 255);
            sphereColor.add("b", libconfig::Setting::TypeInt) = (int)(material->getColor().getB() * 255);
        }
    }
} // namespace Raytracer
