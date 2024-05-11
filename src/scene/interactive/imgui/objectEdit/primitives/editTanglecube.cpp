/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editTanglecube
*/


#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Tanglecube.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editTanglecube(Tanglecube *tanglecube)
    {
        (void)tanglecube;
        #ifdef BONUS
        // Radius
        float radius = tanglecube->getRadius();
        if (ImGui::SliderFloat("Radius", &radius, DEFAULT_RADIUS_MIN,
        18.8, "%.3f")) {
            tanglecube->setRadius(radius);
            m_updateBVH = true;
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

