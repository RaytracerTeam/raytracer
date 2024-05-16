/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonParsing
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer {
    namespace Parsing
    {
        Color getSettingColor(const libconfig::Setting &setting)
        {
            if (!setting.exists("color") || !setting.exists("color.r") ||
            !setting.exists("color.g") || !setting.exists("color.b"))
                return Color(255U, 0, 255);
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
        Math::Vector3D parseVec3D(const libconfig::Setting &setting, const std::string &key,
        Math::Vector3D defaultValue)
        {
            if (setting.exists(key.c_str())) {
                return Math::Vector3D(
                    parseNumber<float>(setting, key + ".x"),
                    parseNumber<float>(setting, key + ".y"),
                    parseNumber<float>(setting, key + ".z")
                );
            }
            return defaultValue;
        }
        float parseRadius(const libconfig::Setting &setting)
        {
            return parseNumber<float>(setting, CFG_RADIUS, 1);
        }
        float parseHeight(const libconfig::Setting &setting)
        {
            return parseNumber<float>(setting, CFG_HEIGHT, 2);
        }
        float parseDistance(const libconfig::Setting &setting)
        {
            return parseNumber<float>(setting, CFG_DISTANCE, 0.5);
        }
        float parseIntensity(const libconfig::Setting &setting)
        {
            return parseNumber<float>(setting, CFG_INTENSITY, 1);
        }
    } // namespace Parsing
} // namespace Raytracer
