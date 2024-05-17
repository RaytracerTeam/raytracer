/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveCone
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Cone.hpp"

namespace Raytracer
{
    void Parsing::saveCone(libconfig::Setting &list, Cone *cone)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, cone->getOrigin());

        libconfig::Setting &radius = setting.add(CFG_RADIUS, libconfig::Setting::TypeFloat);
        radius = cone->getRadius();

        libconfig::Setting &height = setting.add(CFG_HEIGHT, libconfig::Setting::TypeFloat);
        height = cone->getHeight();

        saveMaterial(setting, cone->getMaterial());
    }
} // namespace Raytracer
