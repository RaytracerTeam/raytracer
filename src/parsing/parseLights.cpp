/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseLight
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Lights/PointLight.hpp"

namespace Raytracer {
    namespace Parsing {
        void parseLights(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists("lights"))
                return;

            const libconfig::Setting &lightsSetting = config.lookup("lights");

            for (const auto &lightSetting : lightsSetting.lookup("pointLights")) {
                Math::Vector3D lightPos(0, 0, 0);
                if (lightSetting.exists(CFG_POSITION))
                    lightPos = getSettingPosition(lightSetting);
                Color lightColor(255U, 255U, 255U);
                if (lightSetting.exists(CFG_COLOR))
                    lightColor = getSettingColor(lightSetting);
                double radius = DEFAULT_POINTLIGHT_RADIUS;
                if (lightSetting.exists(CFG_RADIUS))
                    radius = lightSetting.lookup(CFG_RADIUS);
                parseIntensity(lightSetting);
                scene->addLight(std::make_unique<PointLight>(lightPos, radius, lightColor, intensity));
            }
        }
    } // namespace Parsing
} // namespace Raytracer
