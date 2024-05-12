/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCones
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Cone.hpp"

void Raytracer::Parsing::parseCones(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("cones"))
        return;
    for (const auto &config : primitiveSetting.lookup("cones")) {
        auto cone = std::make_unique<Cone>(parsePosition(config),
            parseMaterial(config), parseTransformations(config),
            parseRadius(config),
            parseHeight(config));
        scene->addPrimitive(std::move(cone));
    }
}
