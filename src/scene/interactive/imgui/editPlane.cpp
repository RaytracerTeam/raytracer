/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editPlane
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Plane.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editPlane(Plane *plane)
    {
        #ifdef BONUS
        float planePos = plane->getPos();
        Color planeColor = ((MaterialSolid *)plane->getMaterial())->getColor();
        float planeColorGui[3] = {(float)planeColor.getR(),
            (float)planeColor.getG(), (float)planeColor.getB()};

        if (ImGui::SliderFloat("Position", &planePos, -60, 60
            // , "%.3f", ImGuiSliderFlags_Logarithmic
            )) {
            plane->setPos(planePos);
            m_needRendering = true;
        }
        if (ImGui::ColorEdit3("Color", planeColorGui)) {
            Color newColor = Color(planeColorGui[0], planeColorGui[1], planeColorGui[2]);
            ((MaterialSolid *)plane->getMaterial())->setColor(newColor);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

