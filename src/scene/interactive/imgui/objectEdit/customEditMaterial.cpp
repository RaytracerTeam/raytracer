/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** customEditMaterial
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialCode/Checkerboard.hpp"
#include "Scene/Materials/MaterialTexture/TriangleTexture.hpp"

namespace Raytracer
{
    void SceneInteractive::customEditMaterial(std::unique_ptr<IMaterial> &material)
    {
        switch (material->getType()) {
        case MaterialType::SOLID:
            break;
        case MaterialType::CHECKERBOARD: {
            MaterialCheckerBoard *checkerBoard = static_cast<MaterialCheckerBoard *>(material.get());
            // Color
            ImGui::SetNextItemWidth(200);
            float *color = checkerBoard->getC1();
            if (ImGui::ColorEdit3("Color", color)) {
                checkerBoard->setC1(color);
                m_needRendering = true;
            }
            ImGui::SameLine(0, 20);
            // Color bis
            ImGui::SetNextItemWidth(200);
            float *colorBis = checkerBoard->getC2();
            if (ImGui::ColorEdit3("Color bis", colorBis)) {
                checkerBoard->setC2(colorBis);
                m_needRendering = true;
            }
            ImGui::SameLine(0, 20);
            // Size
            ImGui::SetNextItemWidth(200);
            float size = checkerBoard->getFactor();
            if (ImGui::SliderFloat("Size", &size, 0.01f, 1000.0f, "%.2f",
            ImGuiSliderFlags_Logarithmic)) {
                checkerBoard->setFactor(size);
                m_needRendering = true;
            }
            break;
        }
        case MaterialType::TRIANGLE: {
            TriangleTexture *triangleTexture = static_cast<TriangleTexture *>(material.get());
            // VT1
            float *vt1 = triangleTexture->getVT1();
            if (ImGui::SliderFloat3("VT1", vt1, 0, 1, "%.2f",
            ImGuiSliderFlags_AlwaysClamp)) {
                triangleTexture->setVT1(vt1);
                m_needRendering = true;
            }
            // VT2
            float *vt2 = triangleTexture->getVT2();
            if (ImGui::SliderFloat3("VT2", vt2, 0, 1, "%.2f",
            ImGuiSliderFlags_AlwaysClamp)) {
                triangleTexture->setVT2(vt2);
                m_needRendering = true;
            }
            // VT3
            float *vt3 = triangleTexture->getVT3();
            if (ImGui::SliderFloat3("VT3", vt3, 0, 1, "%.2f",
            ImGuiSliderFlags_AlwaysClamp)) {
                triangleTexture->setVT3(vt3);
                m_needRendering = true;
            }
            break;
        }
        default:
            break;
        }
    }
} // namespace Raytracer
