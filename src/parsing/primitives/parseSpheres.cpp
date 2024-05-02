/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseSphere
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Sphere.hpp"

void Raytracer::Parsing::parseSpheres(const libconfig::Setting &primitiveSetting, Scene &scene)
{
    if (!primitiveSetting.exists("spheres"))
        return;
    for (const auto &config : primitiveSetting.lookup("spheres")) {
        auto sphere = std::make_unique<Sphere>(parsePosition(config),
            std::make_unique<MaterialSolid>(parseColor(config)),
            parseRadius(config));
        // temp
        auto mat = sphere->getMaterial();
        mat->setAlbedo(0.9);
        mat->setFuzzFactor(0.3);
        scene.addPrimitive(std::move(sphere));
    }
}
