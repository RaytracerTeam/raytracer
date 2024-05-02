/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editCylinder
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Cylinder.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editCylinder(Cylinder *cylinder)
    {
        (void)cylinder;
        #ifdef BONUS
        float pos[3] = {(float)cylinder->getOrigin().getX(),
                        (float)cylinder->getOrigin().getY(),
                        (float)cylinder->getOrigin().getZ()};
        Color color = ((MaterialSolid *)cylinder->getMaterial())->getColor();
        float colorGui[3] = {(float)color.getR(),
            (float)color.getG(), (float)color.getB()};
        float radius = cylinder->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, 0, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            cylinder->setRadius(radius);
            m_needRendering = true;
        }

        if (ImGui::SliderFloat3("Position", pos, -60, 60
            // , "%.3f", ImGuiSliderFlags_Logarithmic
            )) {
            cylinder->setOrigin(Math::Vector3D(pos[0], pos[1], pos[2]));
            m_needRendering = true;
        }
        if (ImGui::ColorEdit3("Color", colorGui)) {
            Color newColor = Color(colorGui[0], colorGui[1], colorGui[2]);
            ((MaterialSolid *)cylinder->getMaterial())->setColor(newColor);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

