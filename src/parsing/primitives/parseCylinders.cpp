/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseCylinders
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Cylinder.hpp"

void Raytracer::Parsing::parseCylinders(const libconfig::Setting &primitiveSetting, Scene &scene)
{
    if (!primitiveSetting.exists("cylinders"))
        return;
    for (const auto &config : primitiveSetting.lookup("cylinders")) {
        Math::Vector3D pos(0, 0, 0);
        if (config.exists("position")) {
            pos = getSettingPosition(config);
        }
        MaterialSolid materialSolid(Color(200U, 0U, 200U));
        if (config.exists("color")) {
            materialSolid.setColor(getSettingColor(config));
        }
        float radius = 1;
        if (config.exists("radius")) {
            radius = config.lookup("radius");
        }
        float height = 2;
        if (config.exists("height")) {
            height = config.lookup("height");
        }

        auto cylinder = std::make_unique<Cylinder>(pos,
            std::make_unique<MaterialSolid>(materialSolid),
            radius, height);
        scene.addPrimitive(std::move(cylinder));
    }
}
