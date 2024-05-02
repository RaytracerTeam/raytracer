/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonSaving
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    namespace Parsing
    {
        void Parsing::savePos(libconfig::Setting &setting, APrimitive *primitive)
        {
            libconfig::Setting &pos = setting.add("position", libconfig::Setting::TypeGroup);
            pos.add("x", libconfig::Setting::TypeFloat) = primitive->getOrigin().getX();
            pos.add("y", libconfig::Setting::TypeFloat) = primitive->getOrigin().getY();
            pos.add("z", libconfig::Setting::TypeFloat) = primitive->getOrigin().getZ();
        }
        void Parsing::saveColor(libconfig::Setting &setting, APrimitive *primitive)
        {
            // todo Only works with MaterialSolid
            libconfig::Setting &color = setting.add("color", libconfig::Setting::TypeGroup);
            MaterialSolid *material = dynamic_cast<MaterialSolid *>(primitive->getMaterial());
            if (material) {
                color.add("r", libconfig::Setting::TypeInt) = (int)(material->getColor().getR() * 255);
                color.add("g", libconfig::Setting::TypeInt) = (int)(material->getColor().getG() * 255);
                color.add("b", libconfig::Setting::TypeInt) = (int)(material->getColor().getB() * 255);
            }
        }
    } // namespace Parsing
} // namespace Raytracer

