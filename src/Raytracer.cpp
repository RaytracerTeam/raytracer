/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Raytracer.cpp
*/

#include "Raytracer.hpp"
#include "Scene.hpp"
#include "SceneInteractive.hpp"
#include "Writer.hpp"

#include <string.h>

namespace Raytracer {
    static int interactive(Scene *scene, Dimension &screnDim, const double fov)
    {
        std::unique_ptr<SceneInteractive> interact = std::make_unique<SceneInteractive>(
            screnDim,
            "Raytracer");
        scene->addCamera(std::make_unique<Camera>(screnDim, fov));

        interact->setScene(scene);
        interact->loop();
        return 0;
    }

    static int imageOutput(Scene *scene, Dimension &screnDim, const double fov)
    {
        scene->addCamera(std::make_unique<Camera>(screnDim, fov));

        auto res = scene->render();
        WriteFile::writeImage(WriteFile::PPM, res, screnDim);
        return 0;
    }

    int raytracer(int argc, char **argv)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();
        Dimension dimension(640, 480);
        const double fov = 51.52;
        // struct {size_t x; size_t y;} screnDim = {640, 480};
        // struct {size_t x; size_t y;} screnDim = {1920, 1080};

        if (argc == 2 && strcmp(argv[1], "-i") == 0)
            return interactive(scene.get(), dimension, fov);
        return imageOutput(scene.get(), dimension, fov);
    }
}
