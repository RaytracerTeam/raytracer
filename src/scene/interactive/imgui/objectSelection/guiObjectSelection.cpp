/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjectSelection
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Lights/PointLight.hpp"

namespace Raytracer
{
    void SceneInteractive::guiObjectSelection(void) {
        if (ImGui::BeginTabBar("Object Selection",
        ImGuiTabBarFlags_NoCloseWithMiddleMouseButton
        | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll)) {
            guiPrimitiveTab();
            guiLightTab();
            guiCameraTab();
            guiObjTab();
            guiInventoryTab();
        }
        ImGui::EndTabBar();
        m_selectPrimitiveTab = false;
    }
} // namespace Raytracer
