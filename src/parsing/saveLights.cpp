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
        const SceneLightning &lightSystem = scene.getLightSystem();
        libconfig::Setting &pointLights = lightsSetting.add(CFG_POINT_LIGHTS, libconfig::Setting::TypeList);
        for (auto &light : lightSystem.getLights()) {
            PointLight *pointLight = dynamic_cast<PointLight *>(light.get());
            if (pointLight) {
                libconfig::Setting &lightSetting = pointLights.add(libconfig::Setting::TypeGroup);

                savePos(lightSetting, pointLight->getOrigin());

                saveColor(lightSetting, pointLight->getColor());

                libconfig::Setting &lightIntensity = lightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat);
                lightIntensity = pointLight->getIntensity();
            }
        }
        // Ambient Light
        auto &ambientLightSetting = lightsSetting.add(CFG_AMBIENT_LIGHT, libconfig::Setting::TypeGroup);
        saveColor(ambientLightSetting, lightSystem.getAmbientLights()[0]->getColor());
        ambientLightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat) = lightSystem.getAmbientLights()[0]->getIntensity();

        // Directional Lights
        libconfig::Setting &directionalLights = lightsSetting.add(CFG_DIRECTIONAL_LIGHTS, libconfig::Setting::TypeList);
        const DirectionalLight &directionalLight = scene.getLightSystem().getDirectionLight();

        libconfig::Setting &dLightSetting = directionalLights.add(libconfig::Setting::TypeGroup);

        saveColor(dLightSetting, directionalLight.getColor());
        libconfig::Setting &lightIntensity = dLightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat);
        lightIntensity = directionalLight.getIntensity();

        libconfig::Setting &dirSetting = dLightSetting.add(CFG_DIRECTION, libconfig::Setting::TypeGroup);
        dirSetting.add("x", libconfig::Setting::TypeFloat) = directionalLight.getDirection().getX();
        dirSetting.add("y", libconfig::Setting::TypeFloat) = directionalLight.getDirection().getY();
        dirSetting.add("z", libconfig::Setting::TypeFloat) = directionalLight.getDirection().getZ();
    }
} // namespace Raytracer

