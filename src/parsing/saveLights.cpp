/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveLights
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Lights/PointLight.hpp"

namespace Raytracer
{
    void Parsing::saveLights(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &lightsSetting = root.add("lights", libconfig::Setting::TypeGroup);
        libconfig::Setting &pointLights = lightsSetting.add("pointLights", libconfig::Setting::TypeList);
        for (auto &light : scene.getLights()) {
            PointLight *pointLight = dynamic_cast<PointLight *>(light.get());
            if (pointLight) {
                libconfig::Setting &lightSetting = pointLights.add(libconfig::Setting::TypeGroup);

                savePos(lightSetting, pointLight);

                libconfig::Setting &lightColor = lightSetting.add(CFG_COLOR, libconfig::Setting::TypeGroup);
                lightColor.add("r", libconfig::Setting::TypeInt) = (int)(pointLight->getColor().getR() * 255);
                lightColor.add("g", libconfig::Setting::TypeInt) = (int)(pointLight->getColor().getG() * 255);
                lightColor.add("b", libconfig::Setting::TypeInt) = (int)(pointLight->getColor().getB() * 255);

                libconfig::Setting &lightIntensity = lightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat);
                lightIntensity = pointLight->getIntensity();
            }
        }
        // Ambient Light
        auto &ambientLightSetting = lightsSetting.add(CFG_AMBIENT_LIGHT, libconfig::Setting::TypeGroup);
        libconfig::Setting &alColorSetting = ambientLightSetting.add(CFG_COLOR, libconfig::Setting::TypeGroup);
        Color color = scene.getAmbientLightColor();
        alColorSetting.add("r", libconfig::Setting::TypeInt) = (int)(color.getR() * 255);
        alColorSetting.add("g", libconfig::Setting::TypeInt) = (int)(color.getG() * 255);
        alColorSetting.add("b", libconfig::Setting::TypeInt) = (int)(color.getB() * 255);
        ambientLightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat) = scene.getAmbientLightIntensity();
    }
} // namespace Raytracer

