/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveObj
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void Parsing::saveObj(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &setting = root.add(CFG_OBJ, libconfig::Setting::TypeList);

        auto &objSetting = setting.add(libconfig::Setting::TypeGroup);
        // objSetting.add(CFG_PATH, libconfig::Setting::TypeString) = scene.getObjPath();
    }
} // namespace Raytracer

