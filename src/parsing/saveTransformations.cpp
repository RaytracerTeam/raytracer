/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveTransformations
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Transformations.hpp"

namespace Raytracer {
    namespace Parsing {
        void saveTransformations(libconfig::Setting &setting, APrimitive *primitive)
        {
            libconfig::Setting &transformationsSetting = setting.add(CFG_TRANSFORMATIONS, libconfig::Setting::TypeGroup);

            libconfig::Setting &translationSetting = transformationsSetting.add(CFG_TRANSLATION, libconfig::Setting::TypeGroup);
            translationSetting.add("x", libconfig::Setting::TypeFloat) = primitive->getTranslation().getX();
            translationSetting.add("y", libconfig::Setting::TypeFloat) = primitive->getTranslation().getY();
            translationSetting.add("z", libconfig::Setting::TypeFloat) = primitive->getTranslation().getZ();

            libconfig::Setting &rotationSetting = transformationsSetting.add(CFG_ROTATION, libconfig::Setting::TypeGroup);
            rotationSetting.add("x", libconfig::Setting::TypeFloat) = primitive->getRotation().getX();
            rotationSetting.add("y", libconfig::Setting::TypeFloat) = primitive->getRotation().getY();
            rotationSetting.add("z", libconfig::Setting::TypeFloat) = primitive->getRotation().getZ();

            libconfig::Setting &scaleSetting = transformationsSetting.add(CFG_SCALE, libconfig::Setting::TypeGroup);
            scaleSetting.add("x", libconfig::Setting::TypeFloat) = primitive->getScale().getX();
            scaleSetting.add("y", libconfig::Setting::TypeFloat) = primitive->getScale().getY();
            scaleSetting.add("z", libconfig::Setting::TypeFloat) = primitive->getScale().getZ();
        }
    } // namespace Parsing
} // namespace Raytracer
