/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjectSelection
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::guiObjectSelection(int leftPaneWidth, int imageHeight) {
        #ifdef BONUS
        if (ImGui::BeginTabBar("Object Selection")) {
            if (ImGui::BeginTabItem("Primitives")) {
                m_objectSelection = ObjectSelection::PRIMITIVE;
                ImGui::BeginChild("primitive selection", ImVec2(leftPaneWidth, imageHeight / 2 - 20),
                    ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Primitive", m_selectedObject == 0))
                {
                    // m_scene->addPrimitive(std::make_unique<Sphere>(
                    //     Math::Vector3D(0, 0, 0), 1,
                    //     std::make_unique<MaterialSolid>(
                    //         Color((unsigned int)255, 255, 255)),
                    //     1.0));
                    m_selectedObject = 0;
                }
                int i = 0;
                for (auto &prim : m_scene->getPrimitives())
                {
                    std::string name = std::to_string(i) + " id" +
                        std::to_string(prim->getID()) + " " + prim->getTypeString();

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i + 1))
                        m_selectedObject = i + 1;
                    i++;
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Lights")) {
                m_objectSelection = ObjectSelection::LIGHT;
                ImGui::BeginChild("light selection", ImVec2(leftPaneWidth, imageHeight / 2 - 20),
                    ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Light", m_selectedObject == 0))
                {
                //     m_scene->addLight(std::make_unique<PointLight>(
                //         Math::Vector3D(0, 0, 0), 1, Color(255, 255, 255)));
                    m_selectedObject = 0;
                }
                int i = 0;
                // for (auto &light : m_scene->getLights())
                // {
                //     std::string name = std::to_string(i) + " id" +
                //         std::to_string(light->getID()) + " " + light->getTypeString();

                //     if (ImGui::Selectable(name.c_str(), m_selectedObject == i))
                //         m_selectedObject = i;
                //     i++;
                // }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Cameras")) {
                m_objectSelection = ObjectSelection::CAMERA;
                ImGui::BeginChild("camera selection", ImVec2(leftPaneWidth, imageHeight / 2 - 20),
                    ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Camera", m_selectedObject == 0))
                {
                //     m_scene->addLight(std::make_unique<PointLight>(
                //         Math::Vector3D(0, 0, 0), 1, Color(255, 255, 255)));
                    m_selectedObject = 0;
                }
                ImGui::EndChild();

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        #endif
    }
} // namespace Raytracer
