/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseSphere
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Sphere.hpp"

void Raytracer::Parsing::parseSpheres(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("spheres"))
        return;
    for (const auto &config : primitiveSetting.lookup("spheres")) {
        auto sphere = std::make_unique<Sphere>(parsePosition(config),
            parseMaterial(config, PrimitiveType::SPHERE), parseTransformations(config),
            parseRadius(config));
        scene->addPrimitive(std::move(sphere));
    }
}
