/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiTopBar
*/

#include "Scene/Interactive/SceneInteractive.hpp"


namespace Raytracer
{
    void SceneInteractive::guiTopBar(Camera &currentCamera)
    {
        #ifdef BONUS
        // Render Resolution
        ImGui::SetNextItemWidth(250);
        if (ImGui::SliderInt("Dimension", &m_renderResolution, 10, 4000, "%d",
        ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
            updateDimension(m_renderResolution * SCREEN_RATIO, m_renderResolution);
            m_needRendering = true;
        }

        ImGui::SameLine(0, 50);

        if (ImGui::Button("Render", ImVec2(60, 20)))
            m_needRendering = true;

        ImGui::SameLine(0, 50);

        // FOV
        ImGui::SetNextItemWidth(200);
        float fov = currentCamera.getFov();
        if (ImGui::SliderFloat("FOV", &fov, 1, 179, "%.3f",
        ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
            currentCamera.setFov(fov);
            m_needRendering = true;
        }

        ImGui::SameLine(0, 50);

        ImGui::SetNextItemWidth(200);
        if (ImGui::SliderFloat("Speed", &m_defaultMovementSpeed, 0.01, 10, "%.3f",
        ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
            m_needRendering = true;
        }

        ImGui::SameLine(0, 50);

        // Sensitivity
        ImGui::SetNextItemWidth(200);
        if (ImGui::SliderFloat("Sensitivity", &m_rotationSpeed, 0.1, 100, "%.3f",
        ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer
