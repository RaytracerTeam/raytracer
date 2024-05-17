/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parsePlanes
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Plane.hpp"

void Raytracer::Parsing::parsePlanes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists("planes"))
        return;
    for (const auto &config : primitiveSetting.lookup("planes")) {
        float planePos = 0;
        if (config.exists(CFG_POSITION)) {
            planePos = config.lookup(CFG_POSITION);
        }

        Plane::Axis axis = Plane::Y;
        if (config.exists("axis")) {
            std::string axisStr = config.lookup("axis");
            if (axisStr == "X" || axisStr == "x")
                axis = Plane::X;
            else if (axisStr == "Y" || axisStr == "y")
                axis = Plane::Y;
            else if (axisStr == "Z" || axisStr == "z")
                axis = Plane::Z;
        }
        auto plane = std::make_unique<Plane>(planePos,
            parseMaterial(config, MaterialType::TEXTURE_PLANE),
            parseTransformations(config),
            axis);
        scene->addPrimitive(std::move(plane));
    }
}
