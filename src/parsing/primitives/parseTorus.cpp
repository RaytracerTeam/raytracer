/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseTorus
*/

/*
#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Torus.hpp"

void Raytracer::Parsing::parseTorus(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("cones"))
        return;
    for (const auto &config : primitiveSetting.lookup("cones")) {
        auto torus = std::make_unique<Torus>(parsePosition(config),
            std::make_unique<MaterialSolid>(parseColor(config)),
            parseRadius(config),
            parseDistance(config));
        scene->addPrimitive(std::move(torus));
    }
}
*/
