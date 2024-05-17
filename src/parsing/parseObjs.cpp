/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseObjs
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Obj.hpp"

namespace Raytracer {
    namespace Parsing {
        void parseObjs(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_OBJ))
                return;

            Math::Vector3D position;
            Transformations transformations;

            for (const auto &objSetting : config.lookup(CFG_OBJ)) {
                if (objSetting.exists(CFG_POSITION))
                    position = parsePosition(objSetting);
                if (objSetting.exists(CFG_TRANSFORMATIONS)) {
                    auto &transformationSetting = objSetting.lookup(CFG_TRANSFORMATIONS);
                    transformations.setTranslation(parseVec3D(transformationSetting, CFG_TRANSLATION));
                    transformations.setRotation(parseVec3D(transformationSetting, CFG_ROTATION));
                    transformations.setScale(parseVec3D(transformationSetting, CFG_SCALE, Math::Vector3D(1, 1, 1)));
                }
                if (objSetting.exists(CFG_PATH)) {
                    scene->addObj(std::make_unique<Obj>(
                        position, parseMaterial(objSetting, MaterialType::TEXTURE_TRIANGLE),
                        transformations, objSetting.lookup(CFG_PATH)));
                }
            }
        }
    } // namespace Parsing
} // namespace Raytracer
