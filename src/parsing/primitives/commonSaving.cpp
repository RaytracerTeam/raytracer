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
        void saveVector3D(libconfig::Setting &setting, const std::string &key, const Math::Vector3D vec)
        {
            libconfig::Setting &vecSetting = setting.add(key, libconfig::Setting::TypeGroup);
            vecSetting.add("x", libconfig::Setting::TypeFloat) = vec.getX();
            vecSetting.add("y", libconfig::Setting::TypeFloat) = vec.getY();
            vecSetting.add("z", libconfig::Setting::TypeFloat) = vec.getZ();
        }

        void savePos(libconfig::Setting &setting, const Math::Vector3D pos)
        {
            saveVector3D(setting, CFG_POSITION, pos);
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

