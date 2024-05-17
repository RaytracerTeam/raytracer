/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveCube
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Cube.hpp"

namespace Raytracer
{
    void Parsing::saveCube(libconfig::Setting &list, Cube *cube)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, cube->getOrigin());

        libconfig::Setting &v1 = setting.add(CFG_V1, libconfig::Setting::TypeGroup);
        v1.add("x", libconfig::Setting::TypeFloat) = cube->getVec1().getX();
        v1.add("y", libconfig::Setting::TypeFloat) = cube->getVec1().getY();
        v1.add("z", libconfig::Setting::TypeFloat) = cube->getVec1().getZ();

        saveMaterial(setting, cube->getMaterial());
    }
} // namespace Raytracer
