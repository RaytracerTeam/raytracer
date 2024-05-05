/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editPlane
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Plane.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editPlane(Plane *plane)
    {
        (void)plane;
        #ifdef BONUS

        // Axis
        Plane::Axis axis = plane->getAxis();
        if (ImGui::Combo("Axis", (int *)&axis, "X\0Y\0Z\0\0")) {
            plane->setAxis(axis);
            m_needRendering = true;
        }

        #endif
    }
} // namespace Raytracer

