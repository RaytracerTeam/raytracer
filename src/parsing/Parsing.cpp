/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.cpp
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Lights/PointLight.hpp"

#include <iostream>

namespace Raytracer {
    void printHelper(char *exec)
    {
        std::cout << "USAGE: " << exec << " [OPTIONS] [SCENES]" << std::endl;
        std::cout << "OPTIONS:" << std::endl;
        std::cout << "  -i, --interactive\tInteractive mode" << std::endl;
        std::cout << "  -h, --help\t\tDisplay this help message" << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    namespace Parsing {
        bool parseArgv(int argc, char **argv, std::vector<std::string_view> &inputFiles)
        {
            bool interactiveMode = false;
            const std::vector<std::string_view> args(argv + 1, argv + argc);

            for (const auto& arg : args) {
                if (arg == "-h" || arg == "--help")
                    printHelper(argv[0]);
                if (arg == "-i" || arg == "--interactive") {
                    interactiveMode = true;
                    continue;
                }
                if (!std::filesystem::exists(arg)) {
                    throw std::runtime_error(std::string(arg) + ": No such file or directory");
                }
                inputFiles.push_back(arg);
            }

            return interactiveMode;
        }

        static void parseFile(std::unique_ptr<Scene> &scene, const std::string_view &file)
        {
            libconfig::Config cfg;
            try {
                cfg.readFile(file.data());
            } catch (libconfig::ParseException &e) {
                throw Error(e.getError(), "Parsing::parse");
            }
            parseGlobal(cfg, scene);
            parseOptimization(cfg, scene);
            parseCameras(cfg, scene);
            parsePrimitives(cfg, scene);
            parseLights(cfg, scene);
            parseObj(cfg, scene);
        }
        void parse(std::unique_ptr<Scene> &scene, const std::string_view &file)
        {
            parseFile(scene, file);
        }
        void parse(std::unique_ptr<Scene> &scene, const std::vector<std::string_view> &inputFiles)
        {
            for (const auto& file : inputFiles) {
                parseFile(scene, file);
            }
        }
    } // namespace Parsing
} // namespace Raytracer
