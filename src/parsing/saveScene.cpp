/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveScene
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"

namespace Raytracer
{
    void Parsing::saveScene(const Scene &scene, const std::string &outputFile)
    {
        libconfig::Config cfg;
        libconfig::Setting &root = cfg.getRoot();
        saveCameras(scene, root);
        savePrimitives(scene, root);
        saveLights(scene, root);

        cfg.writeFile(outputFile);
    }
} // namespace Raytracer