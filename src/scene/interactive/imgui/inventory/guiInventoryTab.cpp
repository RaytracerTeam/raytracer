/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjectSelection
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiInventoryTab(void)
    {
        Inventory &inventory = m_scene->getInventory();
        if (ImGui::BeginTabItem("Inventory")) {
            if (m_objectSelection != ObjectSelection::INVENTORY)
                m_selectedObject = inventory.getCurrentMaterialIndex();
            m_objectSelection = ObjectSelection::INVENTORY;
            if (ImGui::BeginChild("primitive selection", ImVec2(m_leftPaneWidth,
            m_imageHeight / 2 - 20), ImGuiChildFlags_Border)) {
                int i = 0;
                for (auto &material : inventory.getMaterials()) {
                    std::string name = std::to_string(i) + " " + material->getTypeString();

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i)) {
                        m_selectedObject = i;
                        inventory.setCurrentMaterialIndex(i);
                    }
                    switch (material->getType()) {
                    case MaterialType::SOLID: {
                        ImGui::SameLine();
                        guiColoredSquare(static_cast<MaterialSolid *>(material.get())->getColor());
                        break;
                    }
                    case MaterialType::TEXTURE:
                    case MaterialType::TEXTURE_CUBE:
                    case MaterialType::TEXTURE_SPHERE:
                    case MaterialType::TEXTURE_PLANE:
                    case MaterialType::TEXTURE_TRIANGLE: {
                        ImGui::SameLine();
                        std::string path = static_cast<MaterialTexture *>(material.get())->getPathname();
                        ImGui::Text("%s", path.substr(path.find_last_of('/') + 1, path.size() - 1).c_str());
                        break;
                    }
                    default:
                        break;
                    }
                    i++;
                }
            }
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
    }
} // namespace Raytracer
