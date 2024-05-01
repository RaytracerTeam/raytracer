/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** handleImGui
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::handleImGui()
    {
        #ifdef BONUS
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        // Start of the window
        ImGui::Begin("What a nice tool, Thank you Mister Pommier", nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

        // Save scene to .cfg
        m_isWriting = false;
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Save as ..."))
            {
                m_isWriting = true;
                std::string hint("custom_scene.cfg");
                if (ImGui::InputTextWithHint(" File name (press ENTER to save)",
                    hint.c_str(), m_fileBuf, FILE_BUF_SIZE, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    Parsing::saveScene(*m_scene, m_fileBuf);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Render Resolution
        ImGui::SetNextItemWidth(300);
        if (ImGui::SliderInt("Dimension", &m_renderResolution, 10, 4000)) {
            updateDimension(m_renderResolution * SCREEN_RATIO, m_renderResolution);
            m_needRendering = true;
        }

        ImGui::SameLine();

        // FOV
        ImGui::SetNextItemWidth(300);
        Camera &currentCamera = m_scene->getCurrentCamera();
        float fov = currentCamera.getFov();
        if (ImGui::SliderFloat("FOV", &fov, 1, 179)) {
            currentCamera.setFov(fov);
            m_needRendering = true;
        }

        ImGui::SameLine();
        ImGui::Checkbox("Show FPS", &m_showFps);
        if (m_showFps)
        {
            ImGui::SameLine();
            ImGui::BeginChild("Debug Infos", ImVec2(250, 30), ImGuiChildFlags_Border);
            // FPS
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            // Camera Pos
            float *pos = currentCamera.getPos();
            if (ImGui::InputFloat3("Pos", pos, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
                // currentCamera.setPos(pos);
                m_needRendering = true;
            }
            // Camera Angle
            float *angle = currentCamera.getAngle();
            if (ImGui::InputFloat3("Angle", angle, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
                // currentCamera.setAngle(angle);
                m_needRendering = true;
            }

            ImGui::EndChild();

        }

        static int selected = 0;
        // Primitive Selection
        ImGui::BeginChild("left pane", ImVec2(150, 300),
            ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
        int i = 0;
        for (auto &prim : m_scene->getPrimitives())
        {
            std::string name = std::to_string(i) + " id" +
                std::to_string(prim->getID()) + " " + prim->getTypeString();

            if (ImGui::Selectable(name.c_str(), selected == i))
                selected = i;
            i++;
        }
        ImGui::EndChild();

        ImGui::SameLine();

        // Image Render
        int imageHeight = ImGui::GetIO().DisplaySize.y - 150;
        int imageWidth = imageHeight * SCREEN_RATIO;
        ImGui::Image(m_texture, sf::Vector2f(
            imageWidth,
            imageHeight),
            sf::Color::White, sf::Color::Cyan);

        editPrimitives(selected);

        ImGui::End();
        ImGui::PopStyleVar();
        #endif
    }
} // namespace Raytracer
