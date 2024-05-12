/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseTransformations
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Transformations.hpp"

namespace Raytracer {
    namespace Parsing
    {
        Transformations parseTransformations(const libconfig::Setting &setting)
        {
            Transformations transformations;

            if (!setting.exists(CFG_TRANSFORMATIONS))
                return transformations;

            libconfig::Setting &transformationsSetting = setting.lookup("transformations");

            transformations.setTranslation(parseVec3D(transformationsSetting, CFG_TRANSLATION));
            transformations.setRotation(parseVec3D(transformationsSetting, CFG_ROTATION));
            transformations.setScale(parseVec3D(transformationsSetting, CFG_SCALE, Math::Vector3D(1, 1, 1)));

            return transformations;
        }
    } // namespace Parsing
} // namespace Raytracer
