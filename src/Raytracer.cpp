/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Raytracer.cpp
*/

#include "Raytracer.hpp"
#include "Parsing/Parsing.hpp"
#include "Scene/Animation.hpp"
#include "Scene/Interactive/SceneInteractive.hpp"
#include "Scene/Scene.hpp"
#include "Writer.hpp"

#include <iostream>
#include <string.h>

namespace Raytracer {
    static int interactive(Dimension &screnDim, std::vector<std::string_view> inputFiles)
    {
        std::unique_ptr<SceneInteractive> interact = std::make_unique<SceneInteractive>(
            screnDim,
            "Raytracer",
            inputFiles);
        interact->loop();
        return 0;
    }

    static int imageOutput(const std::string &path, std::vector<std::string_view> inputFiles, WriteFile::WriteType type, bool animationMode)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();
        Parsing::parse(scene, inputFiles);
        #ifdef BONUSCAMERA
        scene->initRealCamera();
        scene->updateRealCamera();
        #endif
        if (scene->getCameraCount() == 0)
            scene->addCamera(std::make_unique<Camera>());
        scene->updatePrimitives();

        const Dimension &dim = scene->getCurrentCamera().getDimension();
        scene->resizeRender(dim.getWidth(), dim.getHeight());

        if (animationMode) {
            auto animation = std::make_unique<Animation>(path, std::move(scene), dim);
            animation->render(type);
            return 0;
        }

        scene->render();
        scene->waitRendering();

        WriteFile::writeImage(type, path, scene->getRender(), dim);
        return 0;
    }

    static void initFolders(void)
    {
        for (const auto &path : OBJ_PATHS)
            std::filesystem::create_directories(path);
        for (const auto &path : TEXTURE_PATHS)
            std::filesystem::create_directories(path);
        for (const auto &path : SCENE_PATHS)
            std::filesystem::create_directories(path);
        for (const auto &path : SKYBOX_PATHS)
            std::filesystem::create_directories(path);
        std::filesystem::create_directories(CONFIG_DIR);
    }

    int raytracer(int argc, char **argv)
    {
        Dimension windowDimensions(640, 480);

        try {
            std::vector<std::string_view> inputFiles;
            WriteFile::WriteType type = WriteFile::WriteType::PPM;

            initFolders();
            Parsing::ParsingResult parsingRes = Parsing::parseArgv(argc, argv, inputFiles, type);
            if (parsingRes.interactiveMode)
                return interactive(windowDimensions, inputFiles);

            return imageOutput(parsingRes.path, inputFiles, type, parsingRes.animationMode);
        } catch (Error &error) {
            std::cerr << "Error: " << error.what() << ". (" << error.where() << ")" << std::endl;
            return EXIT_FAILURE_EPITECH;
        } catch (const std::runtime_error &error) {
            std::cerr << "Error: " << error.what() << std::endl;
            return EXIT_FAILURE_EPITECH;
        }
    }
}
