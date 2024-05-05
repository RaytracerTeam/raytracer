/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseTriangle
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Triangle.hpp"

void Raytracer::Parsing::parseTriangles(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("triangles"))
        return;
    for (const auto &config : primitiveSetting.lookup("triangles")) {
        auto triangle = std::make_unique<Triangle>(parseVec0(config),
            parseMaterialSolid(config),
            parseVec1(config), parseVec2(config));
        scene->addPrimitive(std::move(triangle));
    }
}
