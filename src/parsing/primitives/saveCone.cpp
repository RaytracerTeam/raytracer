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
    void Parsing::saveCone(const Scene &scene, libconfig::Setting &list, Cone *cone)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, cone);

        libconfig::Setting &radius = setting.add("radius", libconfig::Setting::TypeFloat);
        radius = cone->getRadius();

        libconfig::Setting &height = setting.add("height", libconfig::Setting::TypeFloat);
        height = cone->getHeight();

        saveColor(setting, cone);
    }
} // namespace Raytracer
