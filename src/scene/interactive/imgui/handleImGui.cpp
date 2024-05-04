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

        int imageHeight = ImGui::GetIO().DisplaySize.y - 180;
        int imageWidth = imageHeight * SCREEN_RATIO;
        int leftPaneWidth = ImGui::GetIO().DisplaySize.x - imageWidth - 30;

        // Start of the window
        ImGui::Begin("What a nice tool, Thank you Mister Pommier", nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration);

        //* -- Menu Bar --
        guiMenuBar();

        //* -- Top Bar --
        Camera &currentCamera = m_scene->getCurrentCamera();
        guiTopBar(currentCamera);

        // Left Pane
        ImGui::BeginChild("left pane", ImVec2(leftPaneWidth, imageHeight),
            ImGuiChildFlags_Border);

        //* -- Object Selection --
        guiObjectSelection(leftPaneWidth, imageHeight);

        //* -- Debug Infos --
        if (ImGui::BeginChild("Debug Infos", ImVec2(leftPaneWidth, imageHeight / 2 - 30),
            ImGuiChildFlags_Border)) {
            // FPS
            ImGui::Text("FPS: %.1f", getFramerate());
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
            bool renderLights = m_scene->getRenderLights();
            if (ImGui::Checkbox("Render Lights", &renderLights))
                m_needRendering = true;
            m_scene->setRenderLights(renderLights);

            ImGui::EndChild();
        }
        ImGui::EndChild();

        ImGui::SameLine();

        //* -- Image Render --
        ImGui::Image(m_texture, sf::Vector2f(
            imageWidth,
            imageHeight),
            sf::Color::White, sf::Color::Cyan);

        //* -- Edit Primitives --
        if (m_objectSelection == ObjectSelection::PRIMITIVE) {
            if (m_selectedObject == 0)
                (void) m_selectedObject;
                // addPrimitive();
            else
                guiEditPrimitives();
        } else if (m_objectSelection == ObjectSelection::LIGHT) {
            if (m_selectedObject == 0)
                (void) m_selectedObject;
                // addLight();
            else
                (void) m_selectedObject;
                // editLights();
        }

        ImGui::End();
        ImGui::PopStyleVar();
        #endif
    }
} // namespace Raytracer
