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
        saveGlobal(scene, root);
        saveOptimization(scene, root);
        saveCameras(scene, root);
        saveInventory(scene, root);
        saveObjs(scene, root);
        savePrimitives(scene, root);
        saveLights(scene, root);

        cfg.writeFile(outputFile);
    }
} // namespace Raytracer
