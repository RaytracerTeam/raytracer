/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parsePlane
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Plane.hpp"

void Raytracer::Parsing::parsePlane(const libconfig::Setting &primitiveSetting, Scene &scene)
{
    if (!primitiveSetting.exists("planes"))
        return;
    for (const auto &planeConfig : primitiveSetting.lookup("planes")) {
        float planePos = 0;
        if (planeConfig.exists("position")) {
            planePos = planeConfig.lookup("position");
        }

        MaterialSolid materialSolid(Color(200U, 0U, 200U));
        if (planeConfig.exists("color")) {
            materialSolid.setColor(getSettingColor(planeConfig));
        }

        Plane::Axis axis = Plane::Y;
        if (planeConfig.exists("axis")) {
            std::string axisStr = planeConfig.lookup("axis");
            if (axisStr == "X" || axisStr == "x")
                axis = Plane::X;
            else if (axisStr == "Y" || axisStr == "y")
                axis = Plane::Y;
            else if (axisStr == "Z" || axisStr == "z")
                axis = Plane::Z;
        }
        auto plane = std::make_unique<Plane>(planePos,
            std::make_unique<MaterialSolid>(materialSolid),
            axis);
        scene.addPrimitive(std::move(plane));
    }
}
