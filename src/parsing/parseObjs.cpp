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

            Math::Vector3D translation = Math::Vector3D(0, 0, 0);
            Math::Vector3D scale = Math::Vector3D(1, 1, 1);

            for (const auto &objSetting : config.lookup(CFG_OBJ)) {
                if (objSetting.exists(CFG_POSITION))
                    translation = parsePosition(objSetting);
                if (objSetting.exists(CFG_TRANSFORMATIONS)) {
                    auto &transformationSetting = objSetting.lookup(CFG_TRANSFORMATIONS);
                    scale = parseVec3D(transformationSetting, CFG_SCALE, Math::Vector3D(1, 1, 1));
                }
                if (objSetting.exists(CFG_PATH)) {
                    scene->addObj(std::make_unique<Obj>(
                        objSetting.lookup(CFG_PATH), parseMaterial(objSetting, MaterialType::TEXTURE_TRIANGLE),
                        translation, scale));
                }
            }
        }
    } // namespace Parsing
} // namespace Raytracer
