/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** savePrimitive
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void Parsing::savePrimitives(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &primitivesSetting = root.add("primitives", libconfig::Setting::TypeGroup);
        libconfig::Setting &sphereList = primitivesSetting.add("spheres", libconfig::Setting::TypeList);
        libconfig::Setting &planeList = primitivesSetting.add("planes", libconfig::Setting::TypeList);
        for (auto &primitive : scene.getPrimitives()) {
            Sphere *sphere = dynamic_cast<Sphere *>(primitive.get());
            if (sphere) {
                saveSphere(scene, sphereList, sphere);
                continue;
            }
            Plane *plane = dynamic_cast<Plane *>(primitive.get());
            if (plane) {
                savePlane(scene, planeList, plane);
                continue;
            }
        }
    }
} // namespace Raytracer

