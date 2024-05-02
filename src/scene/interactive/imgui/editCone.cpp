/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editCone
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Cone.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editCone(Cone *cone)
    {
        #ifdef BONUS
        float pos[3] = {(float)cone->getOrigin().getX(),
                        (float)cone->getOrigin().getY(),
                        (float)cone->getOrigin().getZ()};
        Color color = ((MaterialSolid *)cone->getMaterial())->getColor();
        float colorGui[3] = {(float)color.getR(),
            (float)color.getG(), (float)color.getB()};
        // Position
        if (ImGui::SliderFloat3("Position", pos, -60, 60
            // , "%.3f", ImGuiSliderFlags_Logarithmic
            )) {
            cone->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
            m_needRendering = true;
        }
        // Color
        if (ImGui::ColorEdit3("Color", colorGui)) {
            Color newColor = Color(colorGui[0], colorGui[1], colorGui[2]);
            ((MaterialSolid *)cone->getMaterial())->setColor(newColor);
            m_needRendering = true;
        }
        // Radius
        float radius = cone->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, 0, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            cone->setRadius(radius);
            m_needRendering = true;
        }
        // Height
        float height = cone->getHeight();
        if (ImGui::SliderFloat("Height", &height, 0, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            cone->setHeight(height);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

