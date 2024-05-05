/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveTriangle
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Triangle.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveTriangle(libconfig::Setting &triangleList, Triangle *triangle)
    {
        libconfig::Setting &triangleSetting = triangleList.add(libconfig::Setting::TypeGroup);

        libconfig::Setting &v0 = triangleSetting.add(CFG_V0, libconfig::Setting::TypeGroup);
        v0.add("x", libconfig::Setting::TypeFloat) = triangle->getOrigin().getX();
        v0.add("y", libconfig::Setting::TypeFloat) = triangle->getOrigin().getY();
        v0.add("z", libconfig::Setting::TypeFloat) = triangle->getOrigin().getZ();

        libconfig::Setting &v1 = triangleSetting.add(CFG_V1, libconfig::Setting::TypeGroup);
        v1.add("x", libconfig::Setting::TypeFloat) = triangle->getVec1().getX();
        v1.add("y", libconfig::Setting::TypeFloat) = triangle->getVec1().getY();
        v1.add("z", libconfig::Setting::TypeFloat) = triangle->getVec1().getZ();

        libconfig::Setting &v2 = triangleSetting.add(CFG_V2, libconfig::Setting::TypeGroup);
        v2.add("x", libconfig::Setting::TypeFloat) = triangle->getVec2().getX();
        v2.add("y", libconfig::Setting::TypeFloat) = triangle->getVec2().getY();
        v2.add("z", libconfig::Setting::TypeFloat) = triangle->getVec2().getZ();

        saveColor(triangleSetting, triangle);
    }
} // namespace Raytracer
