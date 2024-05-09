/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiAddLight
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiAddLight(void)
    {
        #ifdef BONUS
        SceneLightning &lightSystem = m_scene->getLightSystem();

        if (ImGui::BeginCombo(" ", "Add Light")) {
            if (ImGui::Selectable("Point Light")) {
                auto pointLight = std::make_unique<PointLight>(
                    Math::Vector3D(0, 0, 0),
                    DEFAULT_POINTLIGHT_RADIUS,
                    Color(1., 1, 1),
                    DEFAULT_POINTLIGHT_INTENSITY);
                pointLight->setID(m_scene->getLights().size() + 1);
                lightSystem.addLight(std::move(pointLight));
                m_needRendering = true;
            }
            if (ImGui::Selectable("Directional Light")) {
                auto directionalLight = std::make_unique<DirectionalLight>(
                    Math::Vector3D(-1, 1, -1),
                    Color(1., 1, 1),
                    DEFAULT_AMBIENTLIGHT_INTENSITY);
                // directionalLight->setID(m_scene->getLights().size() + 1);
                lightSystem.addDirectionalLight(std::move(directionalLight));
                m_needRendering = true;
            }
            if (ImGui::Selectable("Ambient Light")) {
                auto ambientLight = std::make_unique<AmbientLight>(
                    Color(1., 1, 1),
                    DEFAULT_AMBIENTLIGHT_INTENSITY);
                // ambientLight->setID(m_scene->getLights().size() + 1);
                lightSystem.addAmbientLight(std::move(ambientLight));
                m_needRendering = true;
            }
            ImGui::EndCombo();
        }
        #endif
    }
} // namespace Raytracer
