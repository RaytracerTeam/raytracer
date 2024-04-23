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
    } // namespace Parsing
} // namespace Raytracer
