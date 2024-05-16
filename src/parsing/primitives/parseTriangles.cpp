/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseTriangle
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Triangle.hpp"

void Raytracer::Parsing::parseTriangles(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("triangles"))
        return;
    for (const auto &config : primitiveSetting.lookup("triangles")) {
        auto triangle = std::make_unique<Triangle>(parsePosition(config),
            parseMaterial(config, PrimitiveType::TRIANGLE),
            parseTransformations(config),
            parseVec3D(config, CFG_V1),
            parseVec3D(config, CFG_V2));

        scene->addPrimitive(std::move(triangle));
    }
}
