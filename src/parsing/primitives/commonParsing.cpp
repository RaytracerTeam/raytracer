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
        Math::Vector3D getSettingPosition(const libconfig::Setting &setting)
        {
            return Math::Vector3D(
                setting.lookup("position.x"),
                setting.lookup("position.y"),
                setting.lookup("position.z")
            );
        }
        Color getSettingColor(const libconfig::Setting &setting)
        {
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

        Math::Vector3D getSettingVec0(const libconfig::Setting &setting)
        {
            return Math::Vector3D(
                setting.lookup("v0.x"),
                setting.lookup("v0.y"),
                setting.lookup("v0.z")
            );
        }
        Math::Vector3D getSettingVec1(const libconfig::Setting &setting)
        {
            return Math::Vector3D(
                setting.lookup("v1.x"),
                setting.lookup("v1.y"),
                setting.lookup("v1.z")
            );
        }
        Math::Vector3D getSettingVec2(const libconfig::Setting &setting)
        {
            return Math::Vector3D(
                setting.lookup("v2.x"),
                setting.lookup("v2.y"),
                setting.lookup("v2.z")
            );
        }

        Math::Vector3D parsePosition(const libconfig::Setting &setting)
        {
            Math::Vector3D pos(0, 0, 0);
            if (setting.exists(CFG_POSITION)) {
                pos = getSettingPosition(setting);
            }
            return pos;
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
        Math::Vector3D parseVec0(const libconfig::Setting &setting)
        {
            Math::Vector3D v0(0, 0, 0);
            if (setting.exists(CFG_V0)) {
                v0 = getSettingVec0(setting);
            }
            return v0;
        }
        Math::Vector3D parseVec1(const libconfig::Setting &setting)
        {
            Math::Vector3D v1(0, 0, 0);
            if (setting.exists(CFG_V1)) {
                v1 = getSettingVec1(setting);
            }
            return v1;
        }
        Math::Vector3D parseVec2(const libconfig::Setting &setting)
        {
            Math::Vector3D v2(0, 0, 0);
            if (setting.exists(CFG_V2)) {
                v2 = getSettingVec2(setting);
            }
            return v2;
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
            return parseFloat(setting, "distance", 0.5);
        }
    } // namespace Parsing
} // namespace Raytracer
