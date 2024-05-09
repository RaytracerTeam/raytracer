/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiDebugInfos
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiDebugInfos(void)
    {
        #ifdef BONUS
        Camera *currentCamera = m_interacCam.getCamera();
        if (ImGui::BeginChild("Debug Infos", ImVec2(m_leftPaneWidth, m_imageHeight / 2 - 30),
        ImGuiChildFlags_Border)) {

            // FPS
            ImGui::Text("FPS: %.1f", getFramerate());
            ImGui::PlotLines("Time/F", m_frameTimes.data(), m_frameTimes.size());
            ImGui::ProgressBar((float)m_scene->getRenderY() / m_dimension.getHeight());
            // Camera Pos
            float *pos = currentCamera->getPos();
            if (ImGui::InputFloat3("Pos", pos, "%.2f")) {
                currentCamera->setPos(pos);
                m_needRendering = true;
            }
            // Camera Angle
            float *angle = currentCamera->getAngle();
            if (ImGui::InputFloat3("Angle", angle, "%.2f")) {
                currentCamera->setAngle(Math::Angle3D(angle[0], angle[1], angle[2]));
                m_needRendering = true;
            }
            // Render lights
            bool renderLights = m_scene->getRenderLights();
            if (ImGui::Checkbox("Render Point Lights", &renderLights))
                m_needRendering = true;
            m_scene->setRenderLights(renderLights);
            // New Render
            if (ImGui::Button("Render", ImVec2(60, 20)))
                m_needRendering = true;

            ImGui::SameLine(0, 20);
            // Resize
            if (ImGui::Button("Resize")) {
                setupImageSize();
            }

            // Ambient light
            float ambientLightIntensity = m_scene->getAmbientLightIntensity();
            if (ImGui::SliderFloat("AL Intens", &ambientLightIntensity, 0, 1)) {
                m_scene->setAmbientLightIntensity(ambientLightIntensity);
                m_needRendering = true;
            }
            float *ambientLightColor = m_scene->getAmbientLightColor();
            if (ImGui::ColorEdit3("AL", ambientLightColor)) {
                m_scene->setAmbientLightColor(ambientLightColor);
                m_needRendering = true;
            }

            int threadNumber = m_scene->getNbThreads();
            if (ImGui::SliderInt("Threads", &threadNumber, 1, m_scene->getMaxNbThreads())) {
                m_scene->setNbThreads(threadNumber);
                m_needRendering = true;
            }

        }
        ImGui::EndChild();
        #endif
    }
} // namespace Raytracer
