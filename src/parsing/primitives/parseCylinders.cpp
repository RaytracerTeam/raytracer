/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCylinders
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Cylinder.hpp"

void Raytracer::Parsing::parseCylinders(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("cylinders"))
        return;
    for (const auto &config : primitiveSetting.lookup("cylinders")) {
        auto cylinder = std::make_unique<Cylinder>(parsePosition(config),
            std::make_unique<MaterialSolid>(parseColor(config)),
            parseRadius(config),
            parseHeight(config));
        scene->addPrimitive(std::move(cylinder));
    }
}