/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveMaterial
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialTexture.hpp"
#include "Scene/Materials/MaterialCode/Checkboard.hpp"

namespace Raytracer
{
    namespace Parsing
    {
        static void saveMaterialSolid(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_SOLID_COLOR;
            MaterialSolid *materialSolid = dynamic_cast<MaterialSolid *>(primitive->getMaterial());
            Color materialColor = materialSolid->getColor();
            saveColor(setting, materialColor);
        }

        static void saveMaterialTexture(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_TEXTURE;
            MaterialTexture *materialTexture = dynamic_cast<MaterialTexture *>(primitive->getMaterial());
            setting.add(CFG_PATH, libconfig::Setting::TypeString) = materialTexture->getPathname();
        }

        static void saveMaterialCheckboard(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_CHECKBOARD;
            MaterialCheckBoard *materialCheckboard = dynamic_cast<MaterialCheckBoard *>(primitive->getMaterial());
            Color color = materialCheckboard->getC1();
            saveColor(setting, color);
            auto &colorBisSetting = setting.add(CFG_COLOR_BIS, libconfig::Setting::TypeGroup);
            Color colorBis = materialCheckboard->getC2();
            saveColor(colorBisSetting, colorBis);
        }

        void saveMaterial(libconfig::Setting &setting, APrimitive *primitive)
        {
            libconfig::Setting &materialSetting = setting.add(CFG_MATERIAL, libconfig::Setting::TypeGroup);
            if (primitive->getMaterial()->getType() == MaterialType::SOLID)
                saveMaterialSolid(materialSetting, primitive);
            else if (primitive->getMaterial()->getType() == MaterialType::TEXTURE)
                saveMaterialTexture(materialSetting, primitive);
            else if (primitive->getMaterial()->getType() == MaterialType::CHECKBOARD)
                saveMaterialCheckboard(materialSetting, primitive);
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

