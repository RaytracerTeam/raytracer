/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCones
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Cone.hpp"

void Raytracer::Parsing::parseCones(const libconfig::Setting &primitiveSetting, Scene &scene)
{
    if (!primitiveSetting.exists("cones"))
        return;
    for (const auto &config : primitiveSetting.lookup("cones")) {
        auto cone = std::make_unique<Cone>(parsePosition(config),
            std::make_unique<MaterialSolid>(parseColor(config)),
            parseRadius(config),
            parseHeight(config));
        scene.addPrimitive(std::move(cone));
    }
}
