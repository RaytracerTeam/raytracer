/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCubes
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Cube.hpp"

void Raytracer::Parsing::parseCubes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("cubes"))
        return;
    for (const auto &config : primitiveSetting.lookup("cubes")) {
        auto cube = std::make_unique<Cube>(parsePosition(config),
            parseMaterial(config, PrimitiveType::CUBE),
            parseVec3D(config, CFG_V1));
        scene->addPrimitive(std::move(cube));
    }
}
