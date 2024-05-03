/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editPrimitives
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::editPrimitives(void)
    {
        int selected = m_selectedObject - 1;

        switch (m_scene->getPrimitives()[selected]->getType())
        {
        case PrimitiveType::SPHERE:
            editSphere(static_cast<Sphere *>(m_scene->getPrimitives()[selected].get()));
            break;
        case PrimitiveType::PLANE:
            editPlane(static_cast<Plane *>(m_scene->getPrimitives()[selected].get()));
            break;
        case PrimitiveType::CYLINDER:
            editCylinder(static_cast<Cylinder *>(m_scene->getPrimitives()[selected].get()));
            break;
        case PrimitiveType::CONE:
            editCone(static_cast<Cone *>(m_scene->getPrimitives()[selected].get()));
            break;
        default:
            break;
        }
    }
} // namespace Raytracer
