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
        void savePos(libconfig::Setting &setting, const Math::Vector3D pos)
        {
            libconfig::Setting &posSetting = setting.add(CFG_POSITION, libconfig::Setting::TypeGroup);
            posSetting.add("x", libconfig::Setting::TypeFloat) = pos.getX();
            posSetting.add("y", libconfig::Setting::TypeFloat) = pos.getY();
            posSetting.add("z", libconfig::Setting::TypeFloat) = pos.getZ();
        }

        void saveColor(libconfig::Setting &setting, const Color color)
        {
            libconfig::Setting &colorSetting = setting.add(CFG_COLOR, libconfig::Setting::TypeGroup);
            colorSetting.add("r", libconfig::Setting::TypeInt) = (int)(color.getR() * 255);
            colorSetting.add("g", libconfig::Setting::TypeInt) = (int)(color.getG() * 255);
            colorSetting.add("b", libconfig::Setting::TypeInt) = (int)(color.getB() * 255);
        }

        void saveMaterialSolid(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_SOLID_COLOR;
            MaterialSolid *materialSolid = dynamic_cast<MaterialSolid *>(primitive->getMaterial());
            Color materialColor = materialSolid->getColor();
            saveColor(setting, materialColor);
        }

        void saveMaterialTexture(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_TEXTURE;
            MaterialTexture *materialTexture = dynamic_cast<MaterialTexture *>(primitive->getMaterial());
            setting.add(CFG_PATH, libconfig::Setting::TypeString) = materialTexture->getPathname();
        }

        void saveMaterial(libconfig::Setting &setting, APrimitive *primitive)
        {
            libconfig::Setting &materialSetting = setting.add(CFG_MATERIAL, libconfig::Setting::TypeGroup);
            if (dynamic_cast<MaterialSolid *>(primitive->getMaterial()))
                saveMaterialSolid(materialSetting, primitive);
            else if (dynamic_cast<MaterialTexture *>(primitive->getMaterial()))
                saveMaterialTexture(materialSetting, primitive);
            else
                throw Error("Unknown material type", "saveMaterial");

            IMaterial *material = primitive->getMaterial();
            if (material) {
                materialSetting.add(CFG_ALBEDO, libconfig::Setting::TypeFloat) = material->getAlbedo();
                materialSetting.add(CFG_TRANSPARENCY, libconfig::Setting::TypeFloat) = material->getTransparency();
                materialSetting.add(CFG_REFRACTION, libconfig::Setting::TypeFloat) = material->getRefraction();
                materialSetting.add(CFG_FUZZ, libconfig::Setting::TypeFloat) = material->getFuzzFactor();
                materialSetting.add(CFG_EMISSION, libconfig::Setting::TypeFloat) = material->getEmission();
                materialSetting.add(CFG_HAS_PHONG, libconfig::Setting::TypeBoolean) = material->hasPhong();
            }
        }
    } // namespace Parsing
} // namespace Raytracer

