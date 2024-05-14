/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseToruses
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Torus.hpp"

void Raytracer::Parsing::parseToruses(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("toruses"))
        return;
    for (const auto &config : primitiveSetting.lookup("toruses")) {
        auto torus = std::make_unique<Torus>(parsePosition(config),
            parseMaterial(config, PrimitiveType::TORUS),
            parseRadius(config),
            parseDistance(config));
        scene->addPrimitive(std::move(torus));
    }
}
