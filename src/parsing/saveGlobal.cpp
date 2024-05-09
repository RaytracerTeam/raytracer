/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveGlobal
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void Parsing::saveGlobal(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &setting = root.add(CFG_GLOBAL, libconfig::Setting::TypeGroup);

        const Skybox &skybox = scene.getSkybox();
        auto &skyboxSetting = setting.add(CFG_SKYBOX, libconfig::Setting::TypeGroup);
        skyboxSetting.add(CFG_HASTEXTURE, libconfig::Setting::TypeBoolean) = skybox.hasTexture();
        saveColor(skyboxSetting, skybox.getSolidColor());
        skyboxSetting.add(CFG_PATH, libconfig::Setting::TypeString) = scene.getSkyboxPath();
    }
} // namespace Raytracer

