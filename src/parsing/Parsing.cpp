/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.cpp
*/

#include "Parsing/Parsing.hpp"

// temp
#include "Scene/Primitives/Cylinder.hpp"
#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

#include "Scene/Lights/PointLight.hpp"

#include <iostream>

namespace Raytracer {
    namespace Parsing {
        bool parseArgv(int argc, char **argv, std::vector<std::string_view> &inputFiles)
        {
            bool interactiveMode = false;
            const std::vector<std::string_view> args(argv + 1, argv + argc);

            for (const auto& arg : args) {
                if (arg == "-i" || arg == "--interactive") {
                    interactiveMode = true;
                    continue;
                }
                if (!std::filesystem::exists(arg)) {
                    throw std::runtime_error(std::string("raytracer: ") + std::string(arg) + ": No such file or directory");
                }
                inputFiles.push_back(arg);
            }

            return interactiveMode;
        }
        void parse(Scene &scene, const std::vector<std::string_view> &inputFiles)
        {
            for (const auto& file : inputFiles) {
                libconfig::Config cfg;
                try {
                    cfg.readFile(file.data());
                } catch (libconfig::ParseException &e) {
                    throw Error(e.getError(), "Parsing::parse");
                }
                parseCameras(cfg, scene);
                parsePrimitives(cfg, scene);
                parseLights(cfg, scene);
            }
            if (scene.getCameraCount() == 0)
                scene.addCamera(std::make_unique<Camera>());
        }
    } // namespace Parsing
} // namespace Raytracer
