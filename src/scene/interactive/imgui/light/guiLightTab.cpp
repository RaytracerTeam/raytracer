/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiLightTab
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiLightTab(void)
    {
        if (ImGui::BeginTabItem("Light")) {
            if (m_objectSelection != ObjectSelection::LIGHT)
                m_selectedObject = -1;
            m_objectSelection = ObjectSelection::LIGHT;
            guiAddLight();
            SceneLightning &lightSystem = m_scene->getLightSystem();
            if (ImGui::BeginChild("light selection", ImVec2(m_leftPaneWidth,
            m_leftPaneChildHeight), ImGuiChildFlags_Border)) {
                int i = 0;
                // Create a vector with all the lights
                std::vector<ILight *> lightVector;
                for (auto &aLight : lightSystem.getAmbientLights())
                    lightVector.push_back(aLight.get());
                for (auto &dLight : lightSystem.getDirectionalLights())
                    lightVector.push_back(dLight.get());
                for (auto &pLight : lightSystem.getLights())
                    lightVector.push_back(pLight.get());

                for (auto &light : lightVector) {
                    std::string name = std::to_string(i) + " " + light->getTypeString();

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i))
                        m_selectedObject = i;
                    ImGui::SameLine();
                    guiColoredSquare(light->getColor());
                    i++;
                }
            }
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
    }
} // namespace Raytracer
