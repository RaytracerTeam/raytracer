/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjTab
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiObjTab(void)
    {
        if (ImGui::BeginTabItem("Obj")) {
            if (m_objectSelection != ObjectSelection::OBJ)
                m_selectedObject = -1;
            m_objectSelection = ObjectSelection::OBJ;
            guiAddObj();
            if (ImGui::BeginChild("obj selection", ImVec2(m_leftPaneWidth,
            m_imageHeight / 2 - 20), ImGuiChildFlags_Border)) {
                int i = 0;
                for (auto &obj : m_scene->getObjs()) {
                    std::string name = std::to_string(i) + " " + obj->getTypeString();
                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i))
                        m_selectedObject = i;
                    if (obj->getMaterial()->getType() == MaterialType::SOLID) {
                        ImGui::SameLine();
                        guiColoredSquare(static_cast<MaterialSolid *>(obj->getMaterial().get())->getColor());
                    }
                    i++;
                }
            }
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
    }
} // namespace Raytracer
