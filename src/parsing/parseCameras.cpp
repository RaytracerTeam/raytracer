/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCameras
*/

#include "Parsing/Parsing.hpp"

void Raytracer::Parsing::parseCameras(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
{
    if (!config.exists("cameras"))
        return;

    for (const auto &cameraSetting : config.lookup("cameras")) {
        Camera camera;
        if (cameraSetting.exists("resolution")) {
            auto &resSetting = cameraSetting.lookup("resolution");
            // camera.setDimension(Dimension(
            //     (unsigned int)resSetting.lookup(CFG_WIDTH),
            //     (unsigned int)resSetting.lookup(CFG_HEIGHT)));
        }
        if (cameraSetting.exists("fieldOfView")) {
            camera.setFov(cameraSetting.lookup("fieldOfView"));
        }
        if (cameraSetting.exists(CFG_POSITION)) {
            camera.setPos(getSettingPosition(cameraSetting));
            camera.setDefaultPos(getSettingPosition(cameraSetting));
        }
        if (cameraSetting.exists(CFG_ROTATION)) {
            camera.setAngle(getSettingRotation(cameraSetting));
            camera.setDefaultAngle(getSettingRotation(cameraSetting));
        }
        scene->addCamera(std::make_unique<Camera>(camera));
    }
}
