/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editPointLight
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Lights/PointLight.hpp"

namespace Raytracer
{
    void SceneInteractive::editPointLight(PointLight *light)
    {
        (void)light;
        #ifdef BONUS
        // Position
        float pos[3] = {(float)light->getOrigin().getX(),
                (float)light->getOrigin().getY(),
                (float)light->getOrigin().getZ()};
        if (ImGui::SliderFloat3("Position", pos, DEFAULT_POS_MIN,
        DEFAULT_POS_MAX)) {
            light->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
            m_needRendering = true;
        }

        // Radius
        float pointLightRadius = light->getRadius();
        if (ImGui::SliderFloat("Radius", &pointLightRadius, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            light->setRadius(pointLightRadius);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer
