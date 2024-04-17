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

        scene.addCamera(std::make_unique<Camera>(640, 480, 51.52));
        auto res = scene.render();
        WriteFile::writeImage(WriteFile::PPM, res, 640, 480);
        return 0;
    }
}
