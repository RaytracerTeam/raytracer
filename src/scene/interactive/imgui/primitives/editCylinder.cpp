/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editCylinder
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Cylinder.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editCylinder(Cylinder *cylinder)
    {
        (void)cylinder;
        #ifdef BONUS
        // Radius
        float radius = cylinder->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            cylinder->setRadius(radius);
            m_needRendering = true;
        }

        // Height
        float height = cylinder->getHeight();
        if (ImGui::SliderFloat("Height", &height, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            cylinder->setHeight(height);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

