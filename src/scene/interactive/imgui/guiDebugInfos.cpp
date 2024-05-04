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
        Camera *currentCamera = m_interacCam.getCamera();
        if (ImGui::BeginChild("Debug Infos", ImVec2(m_leftPaneWidth, m_imageHeight / 2 - 30),
            ImGuiChildFlags_Border)) {
            // FPS
            ImGui::Text("FPS: %.1f", getFramerate());
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
            bool renderLights = m_scene->getRenderLights();
            if (ImGui::Checkbox("Render Lights", &renderLights))
                m_needRendering = true;
            m_scene->setRenderLights(renderLights);

            ImGui::EndChild();
        }
        ImGui::EndChild();
    }
} // namespace Raytracer