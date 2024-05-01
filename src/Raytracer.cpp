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
    static int interactive(Scene *scene, Dimension &screnDim)
    {
        std::unique_ptr<SceneInteractive> interact = std::make_unique<SceneInteractive>(
            screnDim,
            "Raytracer");

        interact->setScene(scene);
        interact->loop();
        return 0;
    }

    static int imageOutput(Scene *scene)
    {
        auto res = scene->render();
        const Dimension &dim = scene->getCurrentCamera().getDimension();

        WriteFile::writeImage(WriteFile::PPM, res, dim);
        return 0;
    }

    int raytracer(int argc, char **argv)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();
        Dimension windowDimensions(640, 480);

        try {
            std::vector<std::string_view> inputFiles;
            bool interactiveMode = Parsing::parseArgv(argc, argv, inputFiles);
            Parsing::parse(*scene, inputFiles);
            scene->updatePrimitives();
            if (interactiveMode)
                return interactive(scene.get(), windowDimensions);
            return imageOutput(scene.get());
        } catch (Error &error) {
            std::cerr << "Error : " << error.what() << ". (" << error.where() << ")" << std::endl;
            return EXIT_FAILURE_EPITECH;
        }
    }
}
