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
        float sphereRadius = sphere->getRadius();
        if (ImGui::SliderFloat("Radius", &sphereRadius, 0.020, 40, "%.3f",
            ImGuiSliderFlags_Logarithmic)) {
            sphere->setRadius(sphereRadius);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

