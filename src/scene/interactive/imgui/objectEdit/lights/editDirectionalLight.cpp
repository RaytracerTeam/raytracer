/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editDirectionalLight
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Lights/DirectionalLight.hpp"

namespace Raytracer
{
    void SceneInteractive::editDirectionalLight(DirectionalLight *light)
    {
        float direction[3] = {
            (float)light->getDirection().getX(),
            (float)light->getDirection().getY(),
            (float)light->getDirection().getZ() };
        if (ImGui::SliderFloat3("Direction", direction, -1, 1, "%.3f", ImGuiSliderFlags_AlwaysClamp)) {
            light->setDirection(Math::Vector3D(direction[0], direction[1], direction[2]));
            m_needRendering = true;
        }
    }
} // namespace Raytracer
