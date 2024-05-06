/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonParsing
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

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
        MaterialSolid parseColor(const libconfig::Setting &setting)
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
        Math::Vector3D parseVec3D(const libconfig::Setting &setting, const std::string &key)
        {
            Math::Vector3D vec(0, 0, 0);
            if (setting.exists(key.c_str())) {
                vec = Math::Vector3D(
                    setting.lookup(key + ".x"),
                    setting.lookup(key + ".y"),
                    setting.lookup(key + ".z")
                );
            }
            return vec;
        }
        float parseFloat(const libconfig::Setting &setting, const std::string &key, float defaultValue = 0.0f)
        {
            if (setting.exists(key.c_str())) {
                defaultValue = setting.lookup(key.c_str());
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
            if (!setting.exists(CFG_MATERIAL))
                return std::make_unique<MaterialSolid>(Color(200U, 0U, 200U));
            libconfig::Setting &materialSetting = setting.lookup("material");
            auto materialSolid = std::make_unique<MaterialSolid>(Color(200U, 0U, 200U));

            if (materialSetting.exists(CFG_COLOR))
                materialSolid->setColor(getSettingColor(materialSetting));

            if (materialSetting.exists(CFG_HAS_PHONG))
                materialSolid->setHasPhong(materialSetting.lookup(CFG_HAS_PHONG));

            if (materialSetting.exists(CFG_ALBEDO))
                materialSolid->setAlbedo(parseFloat(materialSetting, CFG_ALBEDO, 0.0));

            if (materialSetting.exists(CFG_FUZZ))
                materialSolid->setFuzzFactor(parseFloat(materialSetting, CFG_FUZZ, 0.3));

            if (materialSetting.exists(CFG_EMISSION))
                materialSolid->setEmission(parseFloat(materialSetting, CFG_EMISSION, 0.0));

            return materialSolid;
        }
    } // namespace Parsing
} // namespace Raytracer
