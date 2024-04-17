/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Raytracer.cpp
*/

#include "Raytracer.hpp"
#include "Scene.hpp"
#include "Writer.hpp"

namespace Raytracer {
    int raytracer(int argc, char **argv)
    {
        Scene scene;

        auto camera = std::make_unique<Camera>(100, 100, 0.60);
        scene.addCamera(std::move(camera));
        auto res = scene.render();
        WriteFile::writeImage(WriteFile::PNG, res, 100, 100);
        return 0;
    }
}
