/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.hpp
*/

#pragma once

#include <string>
#include <filesystem>
#include <libconfig.h++>
#include "Scene/Scene.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"

namespace Raytracer {
    namespace Parsing {
        bool parseArgv(int argc, char **argv, std::vector<std::string_view> &inputFiles); // return true if interactive mode
        void parse(Scene &scene, const std::vector<std::string_view> &inputFiles);

        void parseCameras(const libconfig::Config &config, Scene &scene);
        void parsePrimitives(const libconfig::Config &config, Scene &scene);
        void parseSphere(const libconfig::Setting &primitiveSetting, Scene &scene);
        void parsePlane(const libconfig::Setting &primitiveSetting, Scene &scene);
        void parseLights(const libconfig::Config &config, Scene &scene);

        void saveScene(const Scene &scene, const std::string &outputFile);
        void saveCameras(const Scene &scene, libconfig::Setting &root);
        void saveLights(const Scene &scene, libconfig::Setting &root);
        void savePrimitives(const Scene &scene, libconfig::Setting &root);
        void saveSphere(const Scene &scene, libconfig::Setting &sphereList, Sphere *sphere);
        void savePlane(const Scene &scene, libconfig::Setting &planeList, Plane *plane);

        Math::Vector3D getSettingPosition(const libconfig::Setting &setting);
        Math::Angle3D getSettingRotation(const libconfig::Setting &setting);
        Color getSettingColor(const libconfig::Setting &setting);
    } // namespace Parsing
} // namespace Raytracing
