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
        libconfig::Setting &objSetting = root.add("objs", libconfig::Setting::TypeList);
        const auto &objs = scene.getObjs();
        for (const auto &obj : objs) {
            libconfig::Setting &setting = objSetting.add(libconfig::Setting::TypeGroup);
            setting.add(CFG_PATH, libconfig::Setting::TypeString) = obj->getObjPath();
            // setting.add(CFG_MATERIAL_TEXTURE, libconfig::Setting::TypeString) = obj->getTexturePath();
            savePos(setting, obj->getOrigin());
            // Save Transformation (Scale)
            auto &trfSetting = setting.add(CFG_TRANSFORMATIONS, libconfig::Setting::TypeGroup);
            saveVector3D(trfSetting, CFG_SCALE, obj->getScale());

            saveMaterial(setting, obj.get());
        }
    }
} // namespace Raytracer
