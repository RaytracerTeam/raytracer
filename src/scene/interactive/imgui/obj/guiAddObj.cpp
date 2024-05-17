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
        if (ImGui::BeginCombo(" ", "Add an Obj")) {
            for (const auto &path : OBJ_PATHS) {
                if (!std::filesystem::exists(path))
                    continue;
                for (const auto &entry : std::filesystem::directory_iterator(path)) {
                    if (ImGui::Selectable(entry.path().filename().string().c_str())) {
                        m_scene->addObj(std::make_unique<Obj>(
                            Math::Vector3D(0, 0, 0),
                            copyMaterial(m_scene->getInventory().getCurrentMaterial().get()),
                            Transformations(),
                            entry.path().string()
                        ));
                        m_updateBVH = true;
                        m_needRendering = true;
                    }
                }
            }
            ImGui::EndCombo();
        }
    }
} // namespace Raytracer
