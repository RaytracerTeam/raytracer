/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.cpp
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Lights/PointLight.hpp"

#ifdef BONUSCAMERA
#include "Scene/Materials/MaterialTexture/CameraTexture.hpp"
#endif

#include <iostream>

namespace Raytracer {
    void printHelper(const std::string_view &exec)
    {
        std::cout << "USAGE: " << exec << " [OPTIONS] [SCENES]" << std::endl;
        std::cout << "OPTIONS:" << std::endl;
        std::cout << "  -i, --interactive\tInteractive mode" << std::endl;
        std::cout << "  -f, --format\t\tOutput format (ppm, jpg, png)" << std::endl;
        std::cout << "  -h, --help\t\tDisplay this help message" << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    namespace Parsing {
        WriteFile::WriteType parseFormat(const std::string_view &format)
        {
            if (format == "ppm")
                return WriteFile::WriteType::PPM;
            else if (format == "jpg")
                return WriteFile::WriteType::JPG;
            else if (format == "png")
                return WriteFile::WriteType::PNG;

            throw std::runtime_error("Invalid format: " + std::string(format));
        }

        bool parseArgv(int argc, char **argv,
            std::vector<std::string_view> &inputFiles, WriteFile::WriteType &type)
        {
            bool interactiveMode = false;
            const std::vector<std::string_view> args(argv, argv + argc);

            for (size_t i = 1; i < args.size(); i++) {
                if (args[i] == "-h" || args[i] == "--help")
                    printHelper(args[0]);
                if (args[i] == "-i" || args[i] == "--interactive") {
                    interactiveMode = true;
                    continue;
                }
                if (args[i] == "-f" || args[i] == "--format") {
                    type = parseFormat(args[++i]);
                    continue;
                }
                if (!std::filesystem::exists(args[i])) {
                    throw std::runtime_error(std::string(args[i]) + ": No such file or directory");
                }
                inputFiles.push_back(args[i]);
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

            // #ifdef BONUSCAMERA
            // for (auto &primitive : scene->getPrimitives()) {
            //     if (primitive->getMaterial()->getType() == MaterialType::CAMERA) {
            //         CameraTexture *cameraTexture = static_cast<CameraTexture *>(primitive->getMaterial().get());
            //         cameraTexture->setCamera(scene->getRealCamera());
            //     }
            // }
            // #endif
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
