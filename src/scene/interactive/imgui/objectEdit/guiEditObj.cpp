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
                ImGui::SameLine(0, 20);
                if (ImGui::Button("Transform to Primitives")) {
                    int primitiveNumber = m_scene->getPrimitives().size();
                    int objIndex = primitiveNumber > 1 ?
                        m_scene->getPrimitives()[primitiveNumber - 1]->getID()
                        + 1 : 0;
                    std::vector<std::unique_ptr<Triangle>> &primitives = obj->getTriangles();
                    for (auto &primitive : primitives) {
                        primitive->setIsPartOfObj(false);
                        primitive->setID(objIndex++);
                        m_scene->addPrimitive(std::move(primitive));
                    }
                    removeSelectedObject();
                    ImGui::EndTabItem();
                    ImGui::EndTabBar();
                    return;
                }

                if (obj->getMaterial()->getType() == MaterialType::SOLID) {
                    // Color
                    ImGui::SetNextItemWidth(200);
                    MaterialSolid *materialSolid = static_cast<MaterialSolid *>(obj->getMaterial().get());
                    float *color = materialSolid->getColor();
                    if (ImGui::ColorEdit3("Color", color)) {
                        materialSolid->setColor(color);
                        obj->setMaterial(std::make_unique<MaterialSolid>(*materialSolid));
                        m_needRendering = true;
                    }
                }

                // Position
                float pos[3] = {(float)obj->getOrigin().getX(),
                        (float)obj->getOrigin().getY(),
                        (float)obj->getOrigin().getZ()};
                if (ImGui::SliderFloat3("Position", pos, DEFAULT_POS_MIN,
                DEFAULT_POS_MAX)) {
                    obj->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
                    m_updateBVH = true;
                    m_needRendering = true;
                }
                ImGui::EndTabItem();
            }

            if (guiEditMaterial(obj->getMaterial())) {
                obj->applyMaterialToTriangles();
                m_needRendering = true;
            }

            if (ImGui::BeginTabItem("Transformations")) {
                // Scale
                float scale[3] = {(float)obj->getScale().getX(),
                        (float)obj->getScale().getY(),
                        (float)obj->getScale().getZ()};
                if (ImGui::SliderFloat3("Scale", scale, 0.01f, 100.0f, "%.2f",
                ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
                    obj->setScale(Math::Vector3D(scale[0], scale[1], scale[2]));
                    m_updateBVH = true;
                    m_needRendering = true;
                }

                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
} // namespace Raytracer
