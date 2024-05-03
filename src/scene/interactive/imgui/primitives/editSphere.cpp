/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editSphere
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editSphere(Sphere *sphere)
    {
        (void)sphere;
        #ifdef BONUS
        float spherePos[3] = {(float)sphere->getOrigin().getX(),
                              (float)sphere->getOrigin().getY(),
                              (float)sphere->getOrigin().getZ()};
        Color sphereColor = ((MaterialSolid *)sphere->getMaterial())->getColor();
        float sphereColorGui[3] = {(float)sphereColor.getR(),
            (float)sphereColor.getG(), (float)sphereColor.getB()};
        float sphereRadius = sphere->getRadius();
        if (ImGui::SliderFloat("Radius", &sphereRadius, 0.020, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            sphere->setRadius(sphereRadius);
            m_needRendering = true;
        }

        if (ImGui::SliderFloat3("Position", spherePos, -60, 60
            // , "%.3f", ImGuiSliderFlags_Logarithmic
            )) {
            sphere->setOrigin(Math::Vector3D(spherePos[0], spherePos[1], spherePos[2]));
            m_needRendering = true;
        }
        if (ImGui::ColorEdit3("Color", sphereColorGui)) {
            Color newColor = Color(sphereColorGui[0], sphereColorGui[1], sphereColorGui[2]);
            ((MaterialSolid *)sphere->getMaterial())->setColor(newColor);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

