/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveMaterial
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialTexture.hpp"
#include "Scene/Materials/MaterialCode/Checkerboard.hpp"

namespace Raytracer
{
    namespace Parsing
    {
        static void saveMaterialSolid(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_SOLID_COLOR;
            MaterialSolid *materialSolid = static_cast<MaterialSolid *>(primitive->getMaterial().get());
            Color materialColor = materialSolid->getColor();
            saveColor(setting, materialColor);
        }

        static void saveMaterialTexture(libconfig::Setting &setting, APrimitive *primitive)
        {
            #ifdef BONUSCAMERA
            if (primitive->getMaterial()->isCamera()) {
                setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_CAMERA;
                return;
            }
            #endif
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_TEXTURE;
            MaterialTexture *materialTexture = static_cast<MaterialTexture *>(primitive->getMaterial().get());
            setting.add(CFG_PATH, libconfig::Setting::TypeString) = materialTexture->getPathname();
        }

        static void saveMaterialCheckerboard(libconfig::Setting &setting, APrimitive *primitive)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_CHECKERBOARD;
            MaterialCheckerBoard *materialCheckerboard = static_cast<MaterialCheckerBoard *>(primitive->getMaterial().get());
            Color color = materialCheckerboard->getC1();
            saveColor(setting, color);
            auto &colorBisSetting = setting.add(CFG_COLOR_BIS, libconfig::Setting::TypeGroup);
            Color colorBis = materialCheckerboard->getC2();
            saveColor(colorBisSetting, colorBis);
            setting.add(CFG_SIZE, libconfig::Setting::TypeFloat) = materialCheckerboard->getFactor();
        }

        void saveMaterial(libconfig::Setting &setting, APrimitive *primitive)
        {
            libconfig::Setting &materialSetting = setting.add(CFG_MATERIAL, libconfig::Setting::TypeGroup);
            switch (primitive->getMaterial()->getType()) {
            case MaterialType::SOLID: saveMaterialSolid(materialSetting, primitive); break;
            case MaterialType::TEXTURE: saveMaterialTexture(materialSetting, primitive); break;
            case MaterialType::TEXTURE_SPHERE: saveMaterialTexture(materialSetting, primitive); break;
            case MaterialType::TEXTURE_TRIANGLE: saveMaterialTexture(materialSetting, primitive); break;
            case MaterialType::TEXTURE_PLANE: saveMaterialTexture(materialSetting, primitive); break;
            case MaterialType::CHECKERBOARD: saveMaterialCheckerboard(materialSetting, primitive); break;
            default:
                break;
            }

            std::unique_ptr<IMaterial> &material = primitive->getMaterial();
            if (material) {
                materialSetting.add(CFG_DIFFUSE, libconfig::Setting::TypeFloat) = material->getDiffuse();
                materialSetting.add(CFG_SPECULAR, libconfig::Setting::TypeFloat) = material->getSpecular();
                materialSetting.add(CFG_SHININESS, libconfig::Setting::TypeFloat) = material->getShininess();
                materialSetting.add(CFG_REFLECTION, libconfig::Setting::TypeFloat) = material->getReflection();
                materialSetting.add(CFG_TRANSPARENCY, libconfig::Setting::TypeFloat) = material->getTransparency();
                materialSetting.add(CFG_REFRACTION, libconfig::Setting::TypeFloat) = material->getRefraction();
            }
        }
    } // namespace Parsing
} // namespace Raytracer

