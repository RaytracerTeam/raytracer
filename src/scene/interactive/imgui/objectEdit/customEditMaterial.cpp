/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** customEditMaterial
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialCode/Checkerboard.hpp"

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
        default:
            break;
        }
    }
} // namespace Raytracer
