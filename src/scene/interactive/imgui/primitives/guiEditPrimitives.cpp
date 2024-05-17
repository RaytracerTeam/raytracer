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
    void SceneInteractive::customEditPrimitives(std::unique_ptr<IPrimitive> &primitive)
    {
        switch (primitive->getType()) {
        case PrimitiveType::SPHERE:
            editSphere(static_cast<Sphere *>(primitive.get()));
            break;
        case PrimitiveType::PLANE:
            editPlane(static_cast<Plane *>(primitive.get()));
            break;
        case PrimitiveType::CYLINDER:
            editCylinder(static_cast<Cylinder *>(primitive.get()));
            break;
        case PrimitiveType::CONE:
            editCone(static_cast<Cone *>(primitive.get()));
            break;
        case PrimitiveType::TORUS:
            editTorus(static_cast<Torus *>(primitive.get()));
            break;
        case PrimitiveType::TANGLECUBE:
            editTanglecube(static_cast<Tanglecube *>(primitive.get()));
            break;
        case PrimitiveType::TRIANGLE:
            editTriangle(static_cast<Triangle *>(primitive.get()));
            break;
        case PrimitiveType::CUBE:
            editCube(static_cast<Cube *>(primitive.get()));
            break;
        default:
            break;
        }
    }

    void SceneInteractive::guiEditPrimitives(void)
    {
        std::unique_ptr<IPrimitive> &primitive = m_scene->getPrimitives()[m_selectedObject];

        if (ImGui::BeginTabBar("Edit Primitives")) {
            if (ImGui::BeginTabItem("Base")) {
                if (ImGui::Button("Delete Primitive")) {
                    removeSelectedObject();
                    ImGui::EndTabItem();
                    ImGui::EndTabBar();
                    return;
                }
                ImGui::SameLine(0, 20);

                // isShown
                bool isShown = primitive->isShown();
                if (ImGui::Checkbox("Is Shown", &isShown)) {
                    primitive->setIsShown(isShown);
                    m_updateBVH = true;
                    m_needRendering = true;
                }

                if (primitive->getMaterial()->getType() == MaterialType::SOLID) {
                    ImGui::SameLine(0, 20);
                    // Color
                    ImGui::SetNextItemWidth(200);
                    MaterialSolid *materialSolid = static_cast<MaterialSolid *>(primitive->getMaterial().get());
                    float *color = materialSolid->getColor();
                    if (ImGui::ColorEdit3("Color", color)) {
                        materialSolid->setColor(color);
                        m_needRendering = true;
                    }
                }

                // Position
                float pos[3] = {(float)primitive->getOrigin().getX(),
                        (float)primitive->getOrigin().getY(),
                        (float)primitive->getOrigin().getZ()};
                if (ImGui::SliderFloat3("Position", pos, DEFAULT_POS_MIN,
                DEFAULT_POS_MAX)) {
                    primitive->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
                    m_updateBVH = true;
                    m_needRendering = true;
                }

                customEditPrimitives(primitive);
                ImGui::EndTabItem();
            }

            if (guiEditMaterial(primitive->getMaterial()))
                m_needRendering = true;

            if (ImGui::BeginTabItem("Transformations")) {
                // Translation
                Math::Vector3D trans3D = primitive->getTranslation();
                float translation[3] = {(float)trans3D.getX(), (float)trans3D.getY(), (float)trans3D.getZ()};
                if (ImGui::SliderFloat3("Translation", translation, DEFAULT_POS_MIN, DEFAULT_POS_MAX)) {
                    primitive->setTranslation(Math::Vector3D(translation[0], translation[1], translation[2]));
                    m_updateBVH = true;
                    m_needRendering = true;
                }
                // Rotation
                Math::Vector3D rot3D = primitive->getRotation();
                float rotation[3] = {(float)rot3D.getX(), (float)rot3D.getY(), (float)rot3D.getZ()};
                if (ImGui::SliderFloat3("Rotation", rotation, 0, 360)) {
                    primitive->setRotation(Math::Vector3D(rotation[0], rotation[1], rotation[2]));
                    m_updateBVH = true;
                    m_needRendering = true;
                }
                // Scale
                Math::Vector3D sca3D = primitive->getScale();
                float scale[3] = {(float)sca3D.getX(), (float)sca3D.getY(), (float)sca3D.getZ()};
                if (ImGui::SliderFloat3("Scale", scale, DEFAULT_RADIUS_MIN, DEFAULT_RADIUS_MAX,
                "%.3f", ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp)) {
                    primitive->setScale(Math::Vector3D(scale[0], scale[1], scale[2]));
                    m_updateBVH = true;
                    m_needRendering = true;
                }
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
} // namespace Raytracer
