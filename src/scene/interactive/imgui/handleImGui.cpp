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

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        // Start of the window
        if (ImGui::Begin("What a nice tool, Thank you Mister Pommier", nullptr,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration)) {

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
            if (m_objectSelection == ObjectSelection::PRIMITIVE) {
                if (m_selectedObject == 0) {
                    (void) m_selectedObject;
                    // addPrimitive();
                } else {
                    guiEditPrimitives();
                }
            } else if (m_objectSelection == ObjectSelection::LIGHT && m_selectedObject > 0) {
                guiEditLights();
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();
        #endif
    }
} // namespace Raytracer
