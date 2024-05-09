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
        default:
            break;
        }
    }
    void SceneInteractive::guiEditPrimitives(void)
    {
        #ifdef BONUS
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

                ImGui::SameLine(0, 20);

                // Color
                ImGui::SetNextItemWidth(200);
                float *color = ((MaterialSolid *)primitive->getMaterial())->getColor();
                if (ImGui::ColorEdit3("Color", color)) {
                    Color newColor = Color(color);
                    ((MaterialSolid *)primitive->getMaterial())->setColor(newColor);
                    m_needRendering = true;
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

            if (ImGui::BeginTabItem("Material")) {
                // Phong
                bool hasPhong = ((MaterialSolid *)primitive->getMaterial())->hasPhong();
                if (ImGui::Checkbox("Phong", &hasPhong)) {
                    ((MaterialSolid *)primitive->getMaterial())->setHasPhong(hasPhong);
                    m_needRendering = true;
                }
                // Albedo
                float albedo = ((MaterialSolid *)primitive->getMaterial())->getAlbedo();
                if (ImGui::SliderFloat("Albedo", &albedo, 0.0f, 2.0f)) {
                    ((MaterialSolid *)primitive->getMaterial())->setAlbedo(albedo);
                    m_needRendering = true;
                }
                // Emissions
                float emission = ((MaterialSolid *)primitive->getMaterial())->getEmission();
                if (ImGui::SliderFloat("Emission", &emission, 0.0f, 2.0f)) {
                    ((MaterialSolid *)primitive->getMaterial())->setEmission(emission);
                    m_needRendering = true;
                }
                // Fuzz
                float fuzz = ((MaterialSolid *)primitive->getMaterial())->getFuzzFactor();
                if (ImGui::SliderFloat("Fuzz", &fuzz, 0.0f, 2.0f)) {
                    ((MaterialSolid *)primitive->getMaterial())->setFuzzFactor(fuzz);
                    m_needRendering = true;
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Transformations")) {
                // Rotation
                Math::Angle3D rot3D = primitive->getTMatrix().getRot();
                float rot[3] = {(float)rot3D.getYaw(), (float)rot3D.getPitch(), (float)rot3D.getRoll()};
                if (ImGui::SliderFloat3("Rotation", rot, 0, 360)) {
                    primitive->setRotXYZ(rot[0], rot[1], rot[2]);
                    m_updateBVH = true;
                    m_needRendering = true;
                }
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
        #endif
    }
} // namespace Raytracer
