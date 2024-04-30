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
        void parseLights(const libconfig::Config &config, Scene &scene)
        {
            if (!config.exists("lights"))
                return;

            const libconfig::Setting &lightsSetting = config.lookup("lights");

            for (const auto &lightSetting : lightsSetting.lookup("pointLights")) {
                Math::Vector3D lightPos(0, 0, 0);
                if (lightSetting.exists("position"))
                    lightPos = getSettingPosition(lightSetting);
                Color lightColor(255U, 255U, 255U);
                if (lightSetting.exists("color"))
                    lightColor = getSettingColor(lightSetting);
                double radius = 0.05;
                if (lightSetting.exists("radius"))
                    radius = lightSetting.lookup("radius");
                double intensity = 1.;
                if (lightSetting.exists("intensity"))
                    intensity = lightSetting.lookup("intensity");
                scene.addLight(std::make_unique<PointLight>(lightPos, radius, lightColor, intensity));
            }
        }
    } // namespace Parsing
} // namespace Raytracer
