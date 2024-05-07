/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiTopBar
*/

#include "Scene/Interactive/SceneInteractive.hpp"


namespace Raytracer
{
    void SceneInteractive::guiTopBar(void)
    {
        #ifdef BONUS
        Camera &currentCamera = m_scene->getCurrentCamera();

        if (ImGui::BeginChild("TopBar", ImVec2(ImGui::GetIO().DisplaySize.x, 30),
        ImGuiChildFlags_AutoResizeX, ImGuiWindowFlags_HorizontalScrollbar)) {
            // Resize
            if (ImGui::Button("Resize")) {
                setupImageSize();
            }

            ImGui::SameLine(0, 50);

            // Render Resolution
            if (ImGui::SliderInt("Dimension", (int *)&m_renderResolution, 10, 4000, "%d",
            ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
                updateDimension(m_renderResolution * SCREEN_RATIO, m_renderResolution);
                m_needRendering = true;
            }

            ImGui::SameLine(0, 50);

            // FOV
            float fov = currentCamera.getFov();
            if (ImGui::SliderFloat("FOV", &fov, 1, 179, "%.3f",
            ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
                currentCamera.setFov(fov);
                m_needRendering = true;
            }

            ImGui::SameLine(0, 50);

            if (ImGui::SliderFloat("Speed", &m_defaultMovementSpeed, 0.01, 10, "%.3f",
            ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
                m_needRendering = true;
            }

            ImGui::SameLine(0, 50);

            // Sensitivity
            if (ImGui::SliderFloat("Sensitivity", &m_rotationSpeed, 0.1, 100, "%.3f",
            ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
                m_needRendering = true;
            }
        }
        ImGui::EndChild();
        #endif
    }
} // namespace Raytracer
