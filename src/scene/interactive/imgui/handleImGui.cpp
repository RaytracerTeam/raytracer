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
        #ifdef BONUS
        ImGui::SFML::Update(m_window, m_deltaClock.restart());

        // ImGui::ShowDemoWindow();
        // return;

        // Plotting Lines
        // Listbox to select primitive type
        // put primitive names next to the enum and get the name in APrimitive
        // Combo to select skybox

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        // Start of the window
        if (ImGui::Begin("What a nice tool, Thank you Mister Pommier", nullptr,
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration)) {

            //* -- Menu Bar --
            guiMenuBar();

            //* -- Top Bar --
            guiTopBar();

            // Left Pane
            if (ImGui::BeginChild("left pane", ImVec2(m_leftPaneWidth, m_imageHeight),
            ImGuiChildFlags_Border)) {

                //* -- Object Selection --
                guiObjectSelection();

                //* -- Debug Infos --
                guiDebugInfos();
            }
            ImGui::EndChild();

            ImGui::SameLine();

            //* -- Image Render --
            ImGui::Image(m_texture, sf::Vector2f(
                m_imageWidth,
                m_imageHeight),
                sf::Color::White, sf::Color::Cyan);

            //* -- Edit Primitives --
            if (m_selectedObject >= 0) {
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
        #endif
    }
} // namespace Raytracer
