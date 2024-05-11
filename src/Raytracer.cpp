/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Raytracer.cpp
*/

#include "Raytracer.hpp"
#include "Parsing/Parsing.hpp"
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

    static void displayLoadingBar(const std::unique_ptr<Scene> &scene)
    {
        int percent = (scene->getRenderY() / scene->getCurrentCamera().getDimension().getHeightD()) * 100;

        std::cout << "Rendering... ";

        std::cout << "\033[1;37m[";
        for (int i = 0; i < percent / 4; i++)
            std::cout << "\033[1;32m=";
        for (int i = percent / 4; i < 25; i++)
            std::cout << "\033[1;37m ";
        std::cout << "\033[1;37m] ";

        std::cout << "\033[1;36m" << percent << "%\r\033[0m" << std::flush;
    }

    static int imageOutput(std::vector<std::string_view> inputFiles, WriteFile::WriteType type)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();
        Parsing::parse(scene, inputFiles);
        if (scene->getCameraCount() == 0)
            scene->addCamera(std::make_unique<Camera>());
        scene->updatePrimitives();

        const Dimension &dim = scene->getCurrentCamera().getDimension();
        scene->resizeRender(dim.getWidth(), dim.getHeight());
        scene->render();

        while (scene->getNbThreadsAlive() > 0)
            displayLoadingBar(scene);

        WriteFile::writeImage(type, scene->getRender(), dim);
        return 0;
    }

    int raytracer(int argc, char **argv)
    {
        Dimension windowDimensions(640, 480);

        try {
            std::vector<std::string_view> inputFiles;
            WriteFile::WriteType type = WriteFile::WriteType::PPM;

            bool interactiveMode = Parsing::parseArgv(argc, argv, inputFiles, type);
            if (interactiveMode)
                return interactive(windowDimensions, inputFiles);

            return imageOutput(inputFiles, type);
        } catch (Error &error) {
            std::cerr << "Error: " << error.what() << ". (" << error.where() << ")" << std::endl;
            return EXIT_FAILURE_EPITECH;
        } catch (const std::runtime_error &error) {
            std::cerr << "Error: " << error.what() << std::endl;
            return EXIT_FAILURE_EPITECH;
        }
    }
}
