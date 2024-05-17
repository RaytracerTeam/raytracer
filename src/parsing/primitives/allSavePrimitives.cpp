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
        libconfig::Setting &sphereList = primitivesSetting.add(CFG_SPHERES, libconfig::Setting::TypeList);
        libconfig::Setting &planeList = primitivesSetting.add("planes", libconfig::Setting::TypeList);
        libconfig::Setting &cylinderList = primitivesSetting.add("cylinders", libconfig::Setting::TypeList);
        libconfig::Setting &coneList = primitivesSetting.add("cones", libconfig::Setting::TypeList);
        libconfig::Setting &torusList = primitivesSetting.add("toruses", libconfig::Setting::TypeList);
        libconfig::Setting &tanglecubeList = primitivesSetting.add("tanglecubes", libconfig::Setting::TypeList);
        libconfig::Setting &triangleList = primitivesSetting.add("triangles", libconfig::Setting::TypeList);
        libconfig::Setting &cubeList = primitivesSetting.add("cubes", libconfig::Setting::TypeList);

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
            case PrimitiveType::TORUS:
                saveTorus(torusList, static_cast<Torus *>(primitive.get()));
                break;
            case PrimitiveType::TANGLECUBE:
                saveTanglecube(tanglecubeList, static_cast<Tanglecube *>(primitive.get()));
                break;
            case PrimitiveType::TRIANGLE:
                saveTriangle(triangleList, static_cast<Triangle *>(primitive.get()));
                break;
            case PrimitiveType::CUBE:
                saveCube(cubeList, static_cast<Cube *>(primitive.get()));
                break;
            default:
                break;
            }
        }
    }
} // namespace Raytracer

