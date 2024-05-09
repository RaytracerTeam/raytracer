/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonParsing
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"

namespace Raytracer {
    namespace Parsing
    {
        Color getSettingColor(const libconfig::Setting &setting)
        {
            if (!setting.exists("color") || !setting.exists("color.r") ||
            !setting.exists("color.g") || !setting.exists("color.b"))
                return Color(255U, 255, 255);
            return Color(
                (unsigned int)setting.lookup("color.r"),
                (unsigned int)setting.lookup("color.g"),
                (unsigned int)setting.lookup("color.b")
            );
        }
        Math::Angle3D getSettingRotation(const libconfig::Setting &setting)
        {
            return Math::Angle3D(
                setting.lookup("rotation.yaw"),
                setting.lookup("rotation.pitch"),
                setting.lookup("rotation.roll")
            );
        }

        Math::Vector3D parsePosition(const libconfig::Setting &setting)
        {
            return parseVec3D(setting, CFG_POSITION);
        }
        MaterialSolid parseMaterialColor(const libconfig::Setting &setting)
        {
            MaterialSolid materialSolid(Color(200U, 0U, 200U));
            if (setting.exists(CFG_COLOR)) {
                materialSolid.setColor(getSettingColor(setting));
            }
            return materialSolid;
        }
        Math::Angle3D parseRotation(const libconfig::Setting &setting)
        {
            Math::Angle3D rotation(0, 0, 0);
            if (setting.exists(CFG_ROTATION)) {
                rotation = getSettingRotation(setting);
            }
            return rotation;
        }
        float parseFloat(const libconfig::Setting &setting, const std::string &key, float defaultValue = 0.0f)
        {
            if (setting.exists(key.c_str())) {
                if (setting.lookup(key.c_str()).getType() == libconfig::Setting::TypeInt)
                    return (float)((int)setting.lookup(key.c_str()));
                return setting.lookup(key.c_str());
            }
            return defaultValue;
        }
        Math::Vector3D parseVec3D(const libconfig::Setting &setting, const std::string &key,
        Math::Vector3D defaultValue)
        {
            if (setting.exists(key.c_str())) {
                return Math::Vector3D(
                    parseFloat(setting, key + ".x"),
                    parseFloat(setting, key + ".y"),
                    parseFloat(setting, key + ".z")
                );
            }
            return defaultValue;
        }
        float parseRadius(const libconfig::Setting &setting)
        {
            return parseFloat(setting, CFG_RADIUS, 1);
        }
        float parseHeight(const libconfig::Setting &setting)
        {
            return parseFloat(setting, CFG_HEIGHT, 2);
        }
        float parseDistance(const libconfig::Setting &setting)
        {
            return parseFloat(setting, CFG_DISTANCE, 0.5);
        }
        float parseIntensity(const libconfig::Setting &setting)
        {
            return parseFloat(setting, CFG_INTENSITY, 1);
        }
        std::unique_ptr<MaterialSolid> parseMaterialSolid(const libconfig::Setting &setting)
        {
            auto materialSolid = std::make_unique<MaterialSolid>(Color(1., 0, 0));

            if (setting.exists(CFG_COLOR))
                materialSolid->setColor(getSettingColor(setting));

            return materialSolid;
        }

        std::unique_ptr<MaterialTexture> parseMaterialTexture(const libconfig::Setting &setting, PrimitiveType primType)
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
                material = parseMaterialSolid(materialSetting);
            else if (materialType == CFG_MATERIAL_TEXTURE)
                material = parseMaterialTexture(materialSetting, primType);
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
