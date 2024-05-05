/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiEditLights
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::guiEditLights(void)
    {
        #ifdef BONUS
        std::unique_ptr<PointLight> &light = m_scene->getLights()[m_selectedObject - 1];

        if (ImGui::Button("Delete Light")) {
            removeSelectedObject();
            return;
        }
        ImGui::SameLine(0, 20);

        // Color
        ImGui::SetNextItemWidth(200);
        float *color = light->getColor();
        if (ImGui::ColorEdit3("Color", color, ImGuiColorEditFlags_PickerHueWheel)) {
            Color newColor = Color(color);
            light->setColor(newColor);
            m_needRendering = true;
        }

        // Position
        float pos[3] = {(float)light->getOrigin().getX(),
                (float)light->getOrigin().getY(),
                (float)light->getOrigin().getZ()};
        if (ImGui::SliderFloat3("Position", pos, DEFAULT_POS_MIN,
        DEFAULT_POS_MAX)) {
            light->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
            m_needRendering = true;
        }

        // Intensity
        float intensity = light->getIntensity();
        if (ImGui::SliderFloat("Intensity", &intensity, DEFAULT_INTENSITY_MIN,
        DEFAULT_INTENSITY_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            light->setIntensity(intensity);
            m_needRendering = true;
        }

        // Radius
        float radius = light->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            light->setRadius(radius);
            m_needRendering = true;
        }

        #endif
    }
} // namespace Raytracer
