/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiEditPrimitives
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::guiEditObjs(void)
    {
        std::unique_ptr<Obj> &obj = m_scene->getObjs()[m_selectedObject];

        if (ImGui::BeginTabBar("Edit Primitives")) {
            if (ImGui::BeginTabItem("Base")) {
                // Prevention
                ImGui::Text("ATTENTION : Changing obj properties is not supported in realtime yet. Please save and reload scene with C.");

                if (ImGui::Button("Delete Obj")) {
                    removeSelectedObject();
                    ImGui::EndTabItem();
                    ImGui::EndTabBar();
                    return;
                }
                ImGui::SameLine(0, 20);

                // isShown
                bool isShown = obj->isShown();
                if (ImGui::Checkbox("Is Shown", &isShown)) {
                    obj->setIsShown(isShown);
                    m_updateBVH = true;
                    m_needRendering = true;
                }

                // Transform to primitives
                if (ImGui::Button("Transform to Primitives")) {
                    std::vector<std::unique_ptr<Triangle>> &primitives = obj->getTriangles();
                    for (auto &primitive : primitives) {
                        primitive->setIsPartOfObj(false);
                        m_scene->addPrimitive(std::move(primitive));
                    }
                    removeSelectedObject();
                    ImGui::EndTabItem();
                    ImGui::EndTabBar();
                    return;
                }

                // if (primitive->getMaterial()->getType() == MaterialType::SOLID) {
                //     ImGui::SameLine(0, 20);
                //     // Color
                //     ImGui::SetNextItemWidth(200);
                //     MaterialSolid *materialSolid = static_cast<MaterialSolid *>(primitive->getMaterial().get());
                //     float *color = materialSolid->getColor();
                //     if (ImGui::ColorEdit3("Color", color)) {
                //         materialSolid->setColor(color);
                //         m_needRendering = true;
                //     }
                // }

                // // Position
                // float pos[3] = {(float)primitive->getOrigin().getX(),
                //         (float)primitive->getOrigin().getY(),
                //         (float)primitive->getOrigin().getZ()};
                // if (ImGui::SliderFloat3("Position", pos, DEFAULT_POS_MIN,
                // DEFAULT_POS_MAX)) {
                //     primitive->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
                //     m_updateBVH = true;
                //     m_needRendering = true;
                // }

                // customEditPrimitives(primitive);
                ImGui::EndTabItem();
            }

            guiEditMaterial(obj->getMaterial());

            if (ImGui::BeginTabItem("Transformations")) {
                // Scale

                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
} // namespace Raytracer
