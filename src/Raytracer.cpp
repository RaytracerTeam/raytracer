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

    static int imageOutput(Scene *scene, Dimension &screnDim)
    {
        auto res = scene->render();

        WriteFile::writeImage(WriteFile::PPM, res, screnDim);
        return 0;
    }

    int raytracer(int argc, char **argv)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();
        Dimension dimension(640, 480); // todo: make it in the scene file, if not set, set thesevalues

        try {
            // MAKE PARSING HERE
            Parsing::parse(*scene, dimension, "");
            // END PARSING
            scene->updatePrimitives();
            if (argc == 2 && strcmp(argv[1], "-i") == 0)
                return interactive(scene.get(), dimension);
            return imageOutput(scene.get(), dimension);
        } catch (Error &error) {
            std::cerr << "Error : " << error.what() << ". (" << error.where() << ")" << std::endl;
            return EXIT_FAILURE_EPITECH;
        }
    }
}
