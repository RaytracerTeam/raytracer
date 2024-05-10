/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseLight
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Lights/PointLight.hpp"
#include "Scene/Lights/DirectionalLight.hpp"
#include "Scene/Lights/AmbientLight.hpp"

namespace Raytracer {
    void Parsing::parseLights(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
    {
        if (!config.exists("lights"))
            return;

        const libconfig::Setting &lightsSetting = config.lookup("lights");

        SceneLightning &lightSystem = scene->getLightSystem();

        // Ambient light
        if (lightsSetting.exists(CFG_AMBIENT_LIGHT)) {
            for (const auto &aLightSetting : lightsSetting[CFG_AMBIENT_LIGHT]) {
                lightSystem.addAmbientLight(std::make_unique<AmbientLight>(
                    getSettingColor(aLightSetting),
                    parseFloat(aLightSetting, CFG_INTENSITY, 0.1)));
            }
        }

        // Point lights
        if (lightsSetting.exists(CFG_POINT_LIGHTS)) {
            for (const auto &setting : lightsSetting[CFG_POINT_LIGHTS]) {
                lightSystem.addLight(std::make_unique<PointLight>(
                    parsePosition(setting),
                    parseRadius(setting),
                    getSettingColor(setting),
                    parseIntensity(setting)));
            }
        }

        // Directional lights
        if (lightsSetting.exists(CFG_DIRECTIONAL_LIGHTS)) {
            for (const auto &dLightSetting : lightsSetting[CFG_DIRECTIONAL_LIGHTS]) {
                lightSystem.addDirectionalLight(std::make_unique<DirectionalLight>(
                    parseVec3D(dLightSetting, CFG_DIRECTION),
                    getSettingColor(dLightSetting),
                    parseIntensity(dLightSetting)));
            }
        }
    }
} // namespace Raytracer
