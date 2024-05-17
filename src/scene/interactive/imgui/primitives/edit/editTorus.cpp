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
        // Radius
        float radius = torus->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            torus->setRadius(radius);
            m_updateBVH = true;
            m_needRendering = true;
        }

        // Distance
        float distance = torus->getDistance();
        if (ImGui::SliderFloat("Distance", &distance, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            torus->setDistance(distance);
            m_updateBVH = true;
            m_needRendering = true;
        }
    }
} // namespace Raytracer

