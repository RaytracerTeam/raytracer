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
        libconfig::Setting &cylinderList = primitivesSetting.add("cylinders", libconfig::Setting::TypeList);
        libconfig::Setting &coneList = primitivesSetting.add("cones", libconfig::Setting::TypeList);
        for (auto &primitive : scene.getPrimitives()) {
            switch (primitive->getType())
            {
            case PrimitiveType::SPHERE:
                saveSphere(sphereList, static_cast<Sphere *>(primitive.get()));
                break;
            case PrimitiveType::PLANE:
                savePlane(planeList, static_cast<Plane *>(primitive.get()));
                break;
            case PrimitiveType::CYLINDER:
                saveCylinder(cylinderList, static_cast<Cylinder *>(primitive.get()));
                break;
            case PrimitiveType::CONE:
                saveCone(coneList, static_cast<Cone *>(primitive.get()));
                break;
            default:
                break;
            }
        }
    }
} // namespace Raytracer

