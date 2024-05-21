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
        try {
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
        } catch (libconfig::FileIOException &e) {
            std::cerr << "Couldn't save file : " << outputFile << std::endl;
        }
    }
} // namespace Raytracer
