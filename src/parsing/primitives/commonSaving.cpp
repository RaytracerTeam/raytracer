/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonSaving
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    namespace Parsing
    {
        void savePos(libconfig::Setting &setting, ISceneObj *obj)
        {
            libconfig::Setting &pos = setting.add(CFG_POSITION, libconfig::Setting::TypeGroup);
            pos.add("x", libconfig::Setting::TypeFloat) = obj->getOrigin().getX();
            pos.add("y", libconfig::Setting::TypeFloat) = obj->getOrigin().getY();
            pos.add("z", libconfig::Setting::TypeFloat) = obj->getOrigin().getZ();
        }

        void saveColor(libconfig::Setting &setting, Color color)
        {
            libconfig::Setting &colorSetting = setting.add(CFG_COLOR, libconfig::Setting::TypeGroup);
            colorSetting.add("r", libconfig::Setting::TypeInt) = (int)(color.getR() * 255);
            colorSetting.add("g", libconfig::Setting::TypeInt) = (int)(color.getG() * 255);
            colorSetting.add("b", libconfig::Setting::TypeInt) = (int)(color.getB() * 255);
        }

        void saveMaterialSolid(libconfig::Setting &setting, APrimitive *primitive)
        {
            libconfig::Setting &material = setting.add("material", libconfig::Setting::TypeGroup);
            material.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_SOLID_COLOR;
            MaterialSolid *materialSolid = dynamic_cast<MaterialSolid *>(primitive->getMaterial());
            Color materialColor = materialSolid->getColor();
            saveColor(material, materialColor);
            if (materialSolid) {
                material.add(CFG_ALBEDO, libconfig::Setting::TypeFloat) = materialSolid->getAlbedo();
                material.add(CFG_FUZZ, libconfig::Setting::TypeFloat) = materialSolid->getFuzzFactor();
                material.add(CFG_EMISSION, libconfig::Setting::TypeFloat) = materialSolid->getEmission();
                material.add(CFG_HAS_PHONG, libconfig::Setting::TypeBoolean) = materialSolid->hasPhong();
            }
        }
    } // namespace Parsing
} // namespace Raytracer

