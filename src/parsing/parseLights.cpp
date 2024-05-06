/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseLight
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Lights/PointLight.hpp"

namespace Raytracer {
    void Parsing::parseLights(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
    {
        if (!config.exists("lights"))
            return;

        const libconfig::Setting &lightsSetting = config.lookup("lights");

        // Ambient light
        if (lightsSetting.exists(CFG_AMBIENT_LIGHT)) {
            auto &ambientLightSetting = lightsSetting[CFG_AMBIENT_LIGHT];
            scene->setAmbientLightColor(getSettingColor(ambientLightSetting));
            scene->setAmbientLightIntensity(parseFloat(ambientLightSetting, CFG_INTENSITY, 0.1));
        }

        // Point lights
        for (const auto &setting : lightsSetting.lookup("pointLights")) {
            scene->addLight(std::make_unique<PointLight>(
                parsePosition(setting),
                parseRadius(setting),
                getSettingColor(setting),
                parseIntensity(setting)));
        }
    }
} // namespace Raytracer
