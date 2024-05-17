/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** savePlane
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Plane.hpp"

namespace Raytracer
{
    void Parsing::savePlane(libconfig::Setting &list, Plane *plane)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        libconfig::Setting &planeNormal = setting.add("axis", libconfig::Setting::TypeString);
        planeNormal = plane->getAxisString();

        libconfig::Setting &planePos = setting.add(CFG_POSITION, libconfig::Setting::TypeFloat);
        Plane::Axis axis = plane->getAxis();
        Math::Vector3D planeOrigin = plane->getOrigin();
        switch (axis) {
        case Plane::Axis::X: planePos = planeOrigin.getX(); break;
        case Plane::Axis::Y: planePos = planeOrigin.getY(); break;
        case Plane::Axis::Z: planePos = planeOrigin.getZ(); break;
        }

        saveMaterial(setting, plane->getMaterial());
        saveTransformations(setting, plane);
    }
} // namespace Raytracer
