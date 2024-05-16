/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiAddObj
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void SceneInteractive::guiAddObj(void)
    {
        if (!std::filesystem::exists(OBJ_PATH)) {
            return;
        }
        ImGui::SetNextItemWidth(200);
        if (ImGui::BeginCombo("Obj Path", "Add an Obj")) {
            for (const auto &entry : std::filesystem::directory_iterator(OBJ_PATH)) {
                if (ImGui::Selectable(entry.path().filename().string().c_str())) {
                    m_scene->addObj(std::make_unique<Obj>(
                        entry.path().string(), std::make_unique<MaterialSolid>(Color(1., 1, 1))
                    ));
                    m_updateBVH = true;
                    m_needRendering = true;
                }
            }
            ImGui::EndCombo();
        }
    }
} // namespace Raytracer
