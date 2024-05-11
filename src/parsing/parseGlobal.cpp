/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseGlobal
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer {
    namespace Parsing {
        void parseGlobal(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_GLOBAL))
                return;
            const libconfig::Setting &setting = config.lookup(CFG_GLOBAL);
            if (setting.exists(CFG_SKYBOX)) {
                auto &skyboxSetting = setting[CFG_SKYBOX];
                Skybox &skybox = scene->getSkybox();
                if (skyboxSetting.exists(CFG_HASTEXTURE))
                    skybox.setHasTexture(skyboxSetting.lookup(CFG_HASTEXTURE));
                else
                    skybox.setHasTexture(false);
                if (skyboxSetting.exists(CFG_PATH))
                    scene->setSkyboxPath(skyboxSetting.lookup(CFG_PATH).c_str());
                if (skyboxSetting.exists(CFG_COLOR))
                    skybox.setSolidColor(getSettingColor(skyboxSetting));
            }
            // if (setting.exists(CFG_CAMERA)) {
            scene->loadRealCamera();
            // }
        }
    } // namespace Parsing
} // namespace Raytracer
