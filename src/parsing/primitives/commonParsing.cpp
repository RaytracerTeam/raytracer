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

        Math::Vector3D parsePosition(const libconfig::Setting &setting)
        {
            Math::Vector3D pos(0, 0, 0);
            if (setting.exists("position")) {
                pos = getSettingPosition(setting);
            }
            return pos;
        }
        MaterialSolid parseColor(const libconfig::Setting &setting)
        {
            MaterialSolid materialSolid(Color(200U, 0U, 200U));
            if (setting.exists("color")) {
                materialSolid.setColor(getSettingColor(setting));
            }
            return materialSolid;
        }
        Math::Angle3D parseRotation(const libconfig::Setting &setting)
        {
            Math::Angle3D rotation(0, 0, 0);
            if (setting.exists("rotation")) {
                rotation = getSettingRotation(setting);
            }
            return rotation;
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
            parseFloat(setting, "radius", 1);
        }
        float parseHeight(const libconfig::Setting &setting)
        {
            parseFloat(setting, "height", 2);
        }
        float parseDistance(const libconfig::Setting &setting)
        {
            parseFloat(setting, "distance", 0.5);
        }
    } // namespace Parsing
} // namespace Raytracer
