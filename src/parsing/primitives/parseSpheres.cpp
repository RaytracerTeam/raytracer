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
    if (!primitiveSetting.exists(CFG_SPHERES))
        return;
    for (const auto &config : primitiveSetting.lookup(CFG_SPHERES)) {
        auto sphere = std::make_unique<Sphere>(parsePosition(config),
            parseMaterial(config, MaterialType::TEXTURE_SPHERE),
            parseTransformations(config),
            parseRadius(config));
        scene->addPrimitive(std::move(sphere));
    }
}
