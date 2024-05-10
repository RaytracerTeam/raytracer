/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonSaving
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    namespace Parsing
    {
        void savePos(libconfig::Setting &setting, const Math::Vector3D pos)
        {
            libconfig::Setting &posSetting = setting.add(CFG_POSITION, libconfig::Setting::TypeGroup);
            posSetting.add("x", libconfig::Setting::TypeFloat) = pos.getX();
            posSetting.add("y", libconfig::Setting::TypeFloat) = pos.getY();
            posSetting.add("z", libconfig::Setting::TypeFloat) = pos.getZ();
        }

        void saveColor(libconfig::Setting &setting, const Color color)
        {
            libconfig::Setting &colorSetting = setting.add(CFG_COLOR, libconfig::Setting::TypeGroup);
            colorSetting.add("r", libconfig::Setting::TypeInt) = (int)(color.getR() * 255);
            colorSetting.add("g", libconfig::Setting::TypeInt) = (int)(color.getG() * 255);
            colorSetting.add("b", libconfig::Setting::TypeInt) = (int)(color.getB() * 255);
        }
    } // namespace Parsing
} // namespace Raytracer

