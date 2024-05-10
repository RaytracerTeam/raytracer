/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseMaterial
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"
#include "Scene/Materials/MaterialCode/Checkboard.hpp"

namespace Raytracer {
    namespace Parsing
    {
        static std::unique_ptr<MaterialTexture> parseMaterialTexture(const libconfig::Setting &setting, PrimitiveType primType)
        {
            if (!setting.exists(CFG_PATH))
                return std::make_unique<MaterialTexture>("");
            switch (primType) {
            case PrimitiveType::SPHERE:
                return std::make_unique<SphereTexture>(setting.lookup(CFG_PATH));
            default:
                return std::make_unique<MaterialTexture>(setting.lookup(CFG_PATH));
            }
        }

        std::unique_ptr<IMaterial> parseMaterial(const libconfig::Setting &setting, PrimitiveType primType) {
            if (!setting.exists(CFG_MATERIAL))
                return std::make_unique<MaterialSolid>(Color(1., 0, 1));
            libconfig::Setting &materialSetting = setting.lookup("material");
            if (!materialSetting.exists(CFG_TYPE))
                return std::make_unique<MaterialSolid>(Color(1., 0, 1));

            std::unique_ptr<IMaterial> material;
            std::string materialType = materialSetting.lookup(CFG_TYPE);
            if (materialType == CFG_MATERIAL_SOLID_COLOR)
                material = std::make_unique<MaterialSolid>(getSettingColor(materialSetting));
            else if (materialType == CFG_MATERIAL_TEXTURE)
                material = parseMaterialTexture(materialSetting, primType);
            else if (materialType == CFG_MATERIAL_CHECKBOARD && materialSetting.exists("color_bis"))
                material = std::make_unique<MaterialCheckBoard>(getSettingColor(materialSetting), getSettingColor(materialSetting.lookup("color_bis")));
            else {
                return std::make_unique<MaterialSolid>(Color(1., 0, 1));
            }

            if (materialSetting.exists(CFG_HAS_PHONG))
                material->setHasPhong(materialSetting.lookup(CFG_HAS_PHONG));

            if (materialSetting.exists(CFG_ALBEDO))
                material->setAlbedo(parseFloat(materialSetting, CFG_ALBEDO, 0.0));

            if (materialSetting.exists(CFG_TRANSPARENCY))
                material->setTransparency(parseFloat(materialSetting, CFG_TRANSPARENCY, 0.0));

            if (materialSetting.exists(CFG_REFRACTION))
                material->setRefraction(parseFloat(materialSetting, CFG_REFRACTION, 1.3));

            if (materialSetting.exists(CFG_FUZZ))
                material->setFuzzFactor(parseFloat(materialSetting, CFG_FUZZ, 0.3));

            if (materialSetting.exists(CFG_EMISSION))
                material->setEmission(parseFloat(materialSetting, CFG_EMISSION, 0.0));

            return material;
        }
    } // namespace Parsing
} // namespace Raytracer
