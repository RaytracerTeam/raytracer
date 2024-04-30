/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCameras
*/

#include "Parsing/Parsing.hpp"

void Raytracer::Parsing::parseCameras(const libconfig::Config &config, Scene &scene)
{
    if (!config.exists("cameras"))
        return;

    for (const auto &cameraSetting : config.lookup("cameras")) {
        Camera camera;
        if (cameraSetting.exists("resolution")) {
            auto &resSetting = cameraSetting.lookup("resolution");
            camera.setDimension(Dimension(
                (unsigned int)resSetting.lookup("width"),
                (unsigned int)resSetting.lookup("height")));
        }
        if (cameraSetting.exists("fieldOfView")) {
            camera.setFov(cameraSetting.lookup("fieldOfView"));
        }
        if (cameraSetting.exists("position")) {
            camera.setPos(getSettingPosition(cameraSetting));
            camera.setDefaultPos(getSettingPosition(cameraSetting));
        }
        if (cameraSetting.exists("rotation")) {
            camera.setAngle(getSettingRotation(cameraSetting));
            camera.setDefaultAngle(getSettingRotation(cameraSetting));
        }
        scene.addCamera(std::make_unique<Camera>(camera));
    }
}
