/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseTanglecubes
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Tanglecube.hpp"

void Raytracer::Parsing::parseTanglecubes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("tanglecubes"))
        return;
    for (const auto &config : primitiveSetting.lookup("tanglecubes")) {
        auto tanglecube = std::make_unique<Tanglecube>(parsePosition(config),
            parseMaterialSolid(config));
        scene->addPrimitive(std::move(tanglecube));
    }
}
