/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiEditInventory
*/

#include "Scene/Interactive/SceneInteractive.hpp"


namespace Raytracer
{
    void SceneInteractive::guiEditInventory(void)
    {
        if (ImGui::BeginTabBar("Edit Material")) {
            guiEditMaterial(m_scene->getInventory().getCurrentMaterial());
        }
        ImGui::EndTabBar();
    }
} // namespace Raytracer
