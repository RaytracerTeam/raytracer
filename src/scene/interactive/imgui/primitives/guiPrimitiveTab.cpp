/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjectSelection
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiPrimitiveTab(void)
    {
        if (ImGui::BeginTabItem("Primitive", nullptr,
        m_selectPrimitiveTab ? ImGuiTabItemFlags_SetSelected : 0)) {
            if (m_objectSelection != ObjectSelection::PRIMITIVE)
                m_selectedObject = -1;
            m_objectSelection = ObjectSelection::PRIMITIVE;
            guiAddPrimitive();
            if (ImGui::BeginChild("primitive selection", ImVec2(m_leftPaneWidth,
            m_leftPaneChildHeight), ImGuiChildFlags_Border)) {
                int i = 0;
                for (auto &prim : m_scene->getPrimitives()) {
                    std::string name = std::to_string(i) + " id" +
                        std::to_string(prim->getID()) + " " + prim->getTypeString();

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i))
                        m_selectedObject = i;
                    if (prim->getMaterial()->getType() == MaterialType::SOLID) {
                        ImGui::SameLine();
                        guiColoredSquare(static_cast<MaterialSolid *>(prim->getMaterial().get())->getColor(), i);
                    }
                    i++;
                }
            }
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
    }
} // namespace Raytracer
