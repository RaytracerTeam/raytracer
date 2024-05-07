/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveCameras
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void Parsing::saveCameras(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &camerasSetting = root.add("cameras", libconfig::Setting::TypeList);
        for (auto &camera : scene.getCameras()) {
            libconfig::Setting &cameraSetting = camerasSetting.add(libconfig::Setting::TypeGroup);

            cameraSetting.add(CFG_RESOLUTION, libconfig::Setting::TypeInt) = (int)camera.get()->getDimension().getHeight();

            libconfig::Setting &cameraPos = cameraSetting.add(CFG_POSITION, libconfig::Setting::TypeGroup);
            cameraPos.add("x", libconfig::Setting::TypeFloat) = camera.get()->getPos().getX();
            cameraPos.add("y", libconfig::Setting::TypeFloat) = camera.get()->getPos().getY();
            cameraPos.add("z", libconfig::Setting::TypeFloat) = camera.get()->getPos().getZ();

            libconfig::Setting &cameraRotation = cameraSetting.add(CFG_ROTATION, libconfig::Setting::TypeGroup);
            cameraRotation.add("yaw", libconfig::Setting::TypeFloat) = fmod(camera.get()->getAngle().getYaw(), 360);
            cameraRotation.add("pitch", libconfig::Setting::TypeFloat) = fmod(camera.get()->getAngle().getPitch(), 360);
            cameraRotation.add("roll", libconfig::Setting::TypeFloat) = fmod(camera.get()->getAngle().getRoll(), 360);

            libconfig::Setting &cameraFov = cameraSetting.add(CFG_FOV, libconfig::Setting::TypeFloat);
            cameraFov = camera.get()->getFov();
        }
    }
} // namespace Raytracer

