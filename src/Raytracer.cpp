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
        // struct {size_t x; size_t y;} screnDim = {640, 480};
        // struct {size_t x; size_t y;} screnDim = {1920, 1080};
        struct {
            size_t x;
            size_t y;
        } screnDim = { 3840, 2160 };

        scene.addCamera(std::make_unique<Camera>(screnDim.x, screnDim.y, 51.52));
        auto res = scene.render();
        WriteFile::writeImage(WriteFile::PPM, res, screnDim.x, screnDim.y);
        return 0;
    }
}
