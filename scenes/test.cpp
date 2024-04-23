/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** test
*/

#include <iostream>
#include <libconfig.h++>

int main(void)
{
    std::cout << "Hello, World!" << std::endl;

    libconfig::Config cfg;
    cfg.readFile("./demo_spheres.cfg");
    auto &cameras = cfg.lookup("cameras");
    float fov;
    int width;
    for (auto &camera : cameras) {
        camera.lookup("resolution").lookupValue("width", width);
        camera.lookupValue("fieldOfView", fov);
        float fieldOfView = camera.lookup("fieldOfView");
        std::cout << fov << " other fov : " << fieldOfView << std::endl;
        std::cout << width << std::endl;
    }

    return 0;
}
