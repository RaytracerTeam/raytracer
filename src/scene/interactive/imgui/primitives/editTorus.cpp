/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editTorus
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Torus.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editTorus(Torus *torus)
    {
        (void)torus;
        #ifdef BONUS
        // Radius
        float radius = torus->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            torus->setRadius(radius);
            m_needRendering = true;
        }

        // Distance
        float distance = torus->getDistance();
        if (ImGui::SliderFloat("Distance", &distance, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            torus->setDistance(distance);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

