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

        // Point Lights
        libconfig::Setting &pointLights = lightsSetting.add(CFG_POINT_LIGHTS, libconfig::Setting::TypeList);
        for (auto &pLight : lightSystem.getLights()) {
            libconfig::Setting &pLightSetting = pointLights.add(libconfig::Setting::TypeGroup);

            savePos(pLightSetting, pLight->getOrigin());
            saveColor(pLightSetting, pLight->getColor());
            pLightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat) = pLight->getIntensity();
        }
        // Ambient Light
        libconfig::Setting &ambientLights = lightsSetting.add(CFG_AMBIENT_LIGHT, libconfig::Setting::TypeList);
        for (auto &aLight : lightSystem.getAmbientLights()) {
            libconfig::Setting &ambientLightSetting = ambientLights.add(libconfig::Setting::TypeGroup);

            saveColor(ambientLightSetting, aLight->getColor());
            ambientLightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat) = aLight->getIntensity();
        }

        // Directional Lights
        libconfig::Setting &dLights = lightsSetting.add(CFG_DIRECTIONAL_LIGHTS, libconfig::Setting::TypeList);
        for (auto &dLight : lightSystem.getDirectionalLights()) {
            libconfig::Setting &dLightSetting = dLights.add(libconfig::Setting::TypeGroup);

            saveColor(dLightSetting, dLight->getColor());
            dLightSetting.add(CFG_INTENSITY, libconfig::Setting::TypeFloat) = dLight->getIntensity();

            saveVector3D(dLightSetting, CFG_DIRECTION, dLight->getDirection());
        }
    }
} // namespace Raytracer

