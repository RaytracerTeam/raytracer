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
                
                libconfig::Setting &lightPos = lightSetting.add("position", libconfig::Setting::TypeGroup);
                lightPos.add("x", libconfig::Setting::TypeFloat) = pointLight->getOrigin().getX();
                lightPos.add("y", libconfig::Setting::TypeFloat) = pointLight->getOrigin().getY();
                lightPos.add("z", libconfig::Setting::TypeFloat) = pointLight->getOrigin().getZ();

                libconfig::Setting &lightColor = lightSetting.add("color", libconfig::Setting::TypeGroup);
                lightColor.add("r", libconfig::Setting::TypeInt) = (int)pointLight->getColor().getR() * 255;
                lightColor.add("g", libconfig::Setting::TypeInt) = (int)pointLight->getColor().getG() * 255;
                lightColor.add("b", libconfig::Setting::TypeInt) = (int)pointLight->getColor().getB() * 255;
            }
        }
    }
} // namespace Raytracer

