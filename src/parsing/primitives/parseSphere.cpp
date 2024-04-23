/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseSphere
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Sphere.hpp"

void Raytracer::Parsing::parseSphere(const libconfig::Setting &primitiveSetting, Scene &scene)
{
    if (!primitiveSetting.exists("spheres"))
        return;
    for (const auto &sphereConfig : primitiveSetting.lookup("spheres")) {
        Math::Vector3D spherePos(0, 0, 0);
        if (sphereConfig.exists("position")) {
            spherePos = getSettingPosition(sphereConfig);
        }
        MaterialSolid materialSolid(Color(200U, 0U, 200U));
        if (sphereConfig.exists("color")) {
            materialSolid.setColor(getSettingColor(sphereConfig));
        }
        auto sphere = std::make_unique<Sphere>(spherePos,
            std::make_unique<MaterialSolid>(materialSolid),
            sphereConfig.lookup("radius"));
        scene.addPrimitive(std::move(sphere));
    }
}
