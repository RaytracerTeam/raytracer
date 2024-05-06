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
        if (cameraSetting.exists(CFG_RESOLUTION)) {
            auto &resSetting = cameraSetting.lookup(CFG_RESOLUTION);
            camera.setDimension(Dimension(
                (unsigned int)resSetting.lookup(CFG_WIDTH),
                (unsigned int)resSetting.lookup(CFG_HEIGHT)));
        }
        if (cameraSetting.exists(CFG_FOV)) {
            camera.setFov(cameraSetting.lookup(CFG_FOV));
        }
        if (cameraSetting.exists(CFG_POSITION)) {
            camera.setPos(parsePosition(cameraSetting));
            camera.setDefaultPos(parsePosition(cameraSetting));
        }
        if (cameraSetting.exists(CFG_ROTATION)) {
            camera.setAngle(getSettingRotation(cameraSetting));
            camera.setDefaultAngle(getSettingRotation(cameraSetting));
        }
        scene->addCamera(std::make_unique<Camera>(camera));
    }
}
