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
        static void saveMaterialSolid(libconfig::Setting &setting,
        const std::unique_ptr<Raytracer::IMaterial> &material)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_SOLID_COLOR;
            MaterialSolid *materialSolid = static_cast<MaterialSolid *>(material.get());
            Color materialColor = materialSolid->getColor();
            saveColor(setting, materialColor);
        }

        static void saveMaterialTexture(libconfig::Setting &setting,
        const std::unique_ptr<Raytracer::IMaterial> &material)
        {
            #ifdef BONUSCAMERA
            if (material->isCamera()) {
                setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_CAMERA;
                return;
            }
            #endif
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_TEXTURE;
            MaterialTexture *materialTexture = static_cast<MaterialTexture *>(material.get());
            setting.add(CFG_PATH, libconfig::Setting::TypeString) = materialTexture->getPathname();
        }

        static void saveMaterialCheckerboard(libconfig::Setting &setting,
        const std::unique_ptr<Raytracer::IMaterial> &material)
        {
            setting.add(CFG_TYPE, libconfig::Setting::TypeString) = CFG_MATERIAL_CHECKERBOARD;
            MaterialCheckerBoard *materialCheckerboard = static_cast<MaterialCheckerBoard *>(material.get());
            Color color = materialCheckerboard->getC1();
            saveColor(setting, color);
            auto &colorBisSetting = setting.add(CFG_COLOR_BIS, libconfig::Setting::TypeGroup);
            Color colorBis = materialCheckerboard->getC2();
            saveColor(colorBisSetting, colorBis);
            setting.add(CFG_SIZE, libconfig::Setting::TypeFloat) = materialCheckerboard->getFactor();
        }

        void saveMaterial(libconfig::Setting &setting, const std::unique_ptr<Raytracer::IMaterial> &material)
        {
            libconfig::Setting &materialSetting = setting.add(CFG_MATERIAL, libconfig::Setting::TypeGroup);
            switch (material->getType()) {
            case MaterialType::SOLID: saveMaterialSolid(materialSetting, material); break;
            case MaterialType::TEXTURE_SPHERE:
            case MaterialType::TEXTURE_TRIANGLE:
            case MaterialType::TEXTURE_PLANE:
            case MaterialType::TEXTURE_CUBE:
            case MaterialType::TEXTURE: saveMaterialTexture(materialSetting, material); break;
            case MaterialType::CHECKERBOARD: saveMaterialCheckerboard(materialSetting, material); break;
            default:
                break;
            }

            if (!material)
                return;
            materialSetting.add(CFG_DIFFUSE, libconfig::Setting::TypeFloat) = material->getDiffuse();
            materialSetting.add(CFG_SPECULAR, libconfig::Setting::TypeFloat) = material->getSpecular();
            materialSetting.add(CFG_SHININESS, libconfig::Setting::TypeFloat) = material->getShininess();
            materialSetting.add(CFG_REFLECTION, libconfig::Setting::TypeFloat) = material->getReflection();
            materialSetting.add(CFG_TRANSPARENCY, libconfig::Setting::TypeFloat) = material->getTransparency();
            materialSetting.add(CFG_REFRACTION, libconfig::Setting::TypeFloat) = material->getRefraction();
        }
    } // namespace Parsing
} // namespace Raytracer

