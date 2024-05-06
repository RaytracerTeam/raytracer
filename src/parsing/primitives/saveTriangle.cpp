/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveTriangle
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Triangle.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveTriangle(libconfig::Setting &list, Triangle *triangle)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, triangle);

        libconfig::Setting &v1 = setting.add(CFG_V1, libconfig::Setting::TypeGroup);
        v1.add("x", libconfig::Setting::TypeFloat) = triangle->getVec1().getX();
        v1.add("y", libconfig::Setting::TypeFloat) = triangle->getVec1().getY();
        v1.add("z", libconfig::Setting::TypeFloat) = triangle->getVec1().getZ();

        libconfig::Setting &v2 = setting.add(CFG_V2, libconfig::Setting::TypeGroup);
        v2.add("x", libconfig::Setting::TypeFloat) = triangle->getVec2().getX();
        v2.add("y", libconfig::Setting::TypeFloat) = triangle->getVec2().getY();
        v2.add("z", libconfig::Setting::TypeFloat) = triangle->getVec2().getZ();

        saveMaterialSolid(setting, triangle);
    }
} // namespace Raytracer