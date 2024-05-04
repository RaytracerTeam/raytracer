/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editCone
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Cone.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editCone(Cone *cone)
    {
        (void)cone;
        #ifdef BONUS
        // Radius
        float radius = cone->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, 0, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            cone->setRadius(radius);
            m_needRendering = true;
        }

        // Height
        float height = cone->getHeight();
        if (ImGui::SliderFloat("Height", &height, 0, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            cone->setHeight(height);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

