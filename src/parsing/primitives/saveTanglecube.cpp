/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveTanglecube
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Tanglecube.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveTanglecube(libconfig::Setting &list, Tanglecube *tanglecube)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, tanglecube->getOrigin());
        saveMaterialSolid(setting, tanglecube);
    }
} // namespace Raytracer
