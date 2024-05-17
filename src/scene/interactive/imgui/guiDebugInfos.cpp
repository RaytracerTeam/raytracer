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
        if (ImGui::BeginChild("Debug Infos", ImVec2(m_leftPaneWidth, m_imageHeight / 2 - 50),
        ImGuiChildFlags_Border)) {

            // FPS
            ImGui::Text("FPS: %.1f", m_framerate);
            ImGui::SliderFloat("MIN FPS", &m_minFramerate, 1, 60, "%.1f",
                ImGuiSliderFlags_AlwaysClamp);
            ImGui::SliderFloat("MAX FPS", &m_maxFramerate, 10, WINDOW_FPS, "%.1f",
                ImGuiSliderFlags_AlwaysClamp);
            ImGui::ProgressBar((float)m_scene->getRenderY() / m_dimension.getHeight());
            // New Render
            if (ImGui::Button("Render", ImVec2(60, 20)))
                m_needRendering = true;
            ImGui::SameLine(0, 20);
            // Resize
            if (ImGui::Button("Resize")) {
                setupImageSize();
            }
            // Render lights
            bool renderLights = m_scene->getRenderLights();
            if (ImGui::Checkbox("Render Point Lights", &renderLights)) {
                m_needRendering = true;
                m_scene->setRenderLights(renderLights);
            }
            // Always Render
            if (ImGui::Checkbox("Always Render", &m_alwaysRender))
                m_scene->setAlwaysRender(m_alwaysRender);
            // Fullscreen
            if (ImGui::Checkbox("Fullscreen", &m_fullscreen))
                setupImageSize();
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

            // Thread number
            int threadNumber = m_scene->getNbThreads();
            if (ImGui::SliderInt("Threads", &threadNumber, 1, m_scene->getMaxNbThreads())) {
                m_scene->setNbThreads(threadNumber);
                m_needRendering = true;
            }

            // Ray Bounces
            int maxRayBounces = m_scene->getMaxRayBounces();
            if (ImGui::SliderInt("Ray Bounces", &maxRayBounces, 1, 10)) {
                m_scene->setMaxRayBounces(maxRayBounces);
                m_needRendering = true;
            }

            // Reach
            ImGui::SliderFloat("Reach", &m_reach, 1, 200, "%.2f",
                ImGuiSliderFlags_Logarithmic);

            // BVH Max Prim Limit
            int bvhMaxPrimLimit = m_scene->getBvhMaxPrimLimit();
            if (ImGui::SliderInt("BVH Max Prim Limit", &bvhMaxPrimLimit, 1, 20,
            "%d", ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_Logarithmic)) {
                m_scene->setBvhMaxPrimLimit(bvhMaxPrimLimit);
                m_updateBVH = true;
                m_needRendering = true;
            }
        }
        ImGui::EndChild();
    }
} // namespace Raytracer
