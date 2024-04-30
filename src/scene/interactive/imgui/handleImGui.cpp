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
        #ifndef BONUS
            return;
        #endif
        ImGui::SFML::Update(m_window, m_deltaClock.restart());
        // ImGui::ShowDemoWindow();
        // return;

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

        if (m_showFps)
        {
            ImGui::SameLine();
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
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

        // Modify Primitive
        switch (m_scene->getPrimitives()[selected]->getType())
        {
        case PrimitiveType::SPHERE:
            editSphere(static_cast<Sphere *>(m_scene->getPrimitives()[selected].get()));
            break;
        case PrimitiveType::PLANE:
            editPlane(static_cast<Plane *>(m_scene->getPrimitives()[selected].get()));
            break;
        default:
            break;
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }
} // namespace Raytracer
