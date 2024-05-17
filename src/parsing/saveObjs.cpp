/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveObj
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Obj.hpp"

namespace Raytracer
{
    void Parsing::saveObjs(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &objSetting = root.add(CFG_OBJ, libconfig::Setting::TypeList);
        const auto &objs = scene.getObjs();
        for (const auto &obj : objs) {
            libconfig::Setting &setting = objSetting.add(libconfig::Setting::TypeGroup);
            setting.add(CFG_PATH, libconfig::Setting::TypeString) = obj->getObjPath();
            savePos(setting, obj->getOrigin());

            saveMaterial(setting, obj->getMaterial());
            saveTransformations(setting, obj.get());
        }
    }
} // namespace Raytracer
