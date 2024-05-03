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

        int imageHeight = ImGui::GetIO().DisplaySize.y - 170;
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

        static int selected = 0;
        //* -- Primitive Selection --
        if (ImGui::BeginTabBar("Primitive Selection")) {
            if (ImGui::BeginTabItem("Primitives")) {
                ImGui::BeginChild("primitive selection", ImVec2(leftPaneWidth, imageHeight / 2 - 20),
                    ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Primitive", selected == 0))
                {
                    // m_scene->addPrimitive(std::make_unique<Sphere>(
                    //     Math::Vector3D(0, 0, 0), 1, std::make_unique<MaterialSolid>()));
                    selected = 0;
                }
                int i = 0;
                for (auto &prim : m_scene->getPrimitives())
                {
                    std::string name = std::to_string(i) + " id" +
                        std::to_string(prim->getID()) + " " + prim->getTypeString();

                    if (ImGui::Selectable(name.c_str(), selected == i + 1))
                        selected = i + 1;
                    i++;
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Lights")) {
                // ImGui::BeginChild("light selection", ImVec2(leftPaneWidth, imageHeight / 2 - 30),
                //     ImGuiChildFlags_Border);
                // int i = 0;
                // if (ImGui::Selectable("Add Light", selected == i))
                // {
                //     m_scene->addLight(std::make_unique<PointLight>(
                //         Math::Vector3D(0, 0, 0), 1, Color(255, 255, 255)));
                //     selected = i;
                // }
                // for (auto &light : m_scene->getLights())
                // {
                //     std::string name = std::to_string(i) + " id" +
                //         std::to_string(light->getID()) + " " + light->getTypeString();

                //     if (ImGui::Selectable(name.c_str(), selected == i))
                //         selected = i;
                //     i++;
                // }
                // ImGui::EndChild();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        //* -- Debug Infos --
        ImGui::BeginChild("Debug Infos", ImVec2(leftPaneWidth, imageHeight / 2 - 30),
            ImGuiChildFlags_Border);
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
        bool renderLights = m_scene->getRenderLights();
        if (ImGui::Checkbox("Render Lights", &renderLights))
            m_needRendering = true;
        m_scene->setRenderLights(renderLights);

        ImGui::EndChild();

        ImGui::EndChild();

        ImGui::SameLine();

        //* -- Image Render --
        ImGui::Image(m_texture, sf::Vector2f(
            imageWidth,
            imageHeight),
            sf::Color::White, sf::Color::Cyan);

        //* -- Edit Primitives --
        if (selected == 0)
            (void) selected;
            // addPrimitive();
        else
            editPrimitives(selected - 1);

        ImGui::End();
        ImGui::PopStyleVar();
        #endif
    }
} // namespace Raytracer
