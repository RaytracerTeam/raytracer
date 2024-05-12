/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** handleImGui
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::handleImGui()
    {
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        // Start of the window
        if (ImGui::Begin("What a nice tool, Thank you Mister Pommier", nullptr,
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration)) {
            if (!m_fullscreen) {
                //* -- Menu Bar --
                guiMenuBar();

                //* -- Top Bar --
                guiTopBar();

                // Left Pane
                if (ImGui::BeginChild("left pane", ImVec2(m_leftPaneWidth, m_imageHeight),
                ImGuiChildFlags_Border, ImGuiWindowFlags_NoScrollbar)) {

                    //* -- Object Selection --
                    guiObjectSelection();

                    //* -- Debug Infos --
                    guiDebugInfos();
                }
                ImGui::EndChild();

                ImGui::SameLine();
            }

            //* -- Image Render --
            ImGui::Image(m_texture, sf::Vector2f(
                m_imageWidth,
                m_imageHeight),
                sf::Color::White, sf::Color::Cyan);

            //* -- Edit Primitives --
            if (!m_fullscreen && m_selectedObject >= 0) {
                switch (m_objectSelection) {
                case ObjectSelection::PRIMITIVE: guiEditPrimitives(); break;
                case ObjectSelection::LIGHT: guiEditLights(); break;
                case ObjectSelection::CAMERA: guiEditCameras(); break;
                default: break;
                }
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void SceneInteractive::setupImageSize()
    {
        m_imageWidth = ImGui::GetIO().DisplaySize.x - 20;
        if (!m_fullscreen)
            m_imageWidth -= m_leftPaneWidth + 30;
        m_imageHeight = m_imageWidth / (SCREEN_RATIO);
    }
} // namespace Raytracer
