/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiEditLights
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::customEditLights(ILight *light)
    {
        switch (light->getType()) {
        case LightType::AMBIENT:
            break;
        case LightType::POINT:
            editPointLight(static_cast<PointLight *>(light));
            break;
        case LightType::DIRECTIONAL:
            editDirectionalLight(static_cast<DirectionalLight *>(light));
            break;
        case LightType::SPOT:
            break;
        default:
            break;
        }
    }
    void SceneInteractive::guiEditLights(void)
    {
        #ifdef BONUS
        if (m_selectedObject < 0)
            return;
        SceneLightning &lightSystem = m_scene->getLightSystem();
        ILight *light = nullptr;
        size_t localSelectedObject = m_selectedObject;
        std::vector<std::unique_ptr<AmbientLight>> &ambientLights = lightSystem.getAmbientLights();
        std::vector<std::unique_ptr<PointLight>> &pointLights = lightSystem.getLights();
        std::vector<std::unique_ptr<DirectionalLight>> &directionalLights = lightSystem.getDirectionalLights();

        if (localSelectedObject < ambientLights.size())
            light = ambientLights[localSelectedObject].get();
        localSelectedObject -= ambientLights.size();
        if (localSelectedObject < directionalLights.size())
            light = directionalLights[localSelectedObject].get();
        localSelectedObject -= directionalLights.size();
        if (localSelectedObject < pointLights.size())
            light = pointLights[localSelectedObject].get();
        localSelectedObject -= pointLights.size();

        if (!light)
            return;

        if (ImGui::Button("Delete Light")) {
            removeSelectedObject();
            return;
        }

        // Color
        ImGui::SetNextItemWidth(200);
        float *color = light->getColor();
        if (ImGui::ColorEdit3("Color", color)) {
            Color newColor = Color(color);
            light->setColor(newColor);
            m_needRendering = true;
        }

        // Intensity
        float intensity = light->getIntensity();
        if (ImGui::SliderFloat("Intensity", &intensity, DEFAULT_INTENSITY_MIN,
        DEFAULT_INTENSITY_MAX)) {
            light->setIntensity(intensity);
            m_needRendering = true;
        }

        customEditLights(light);

        #endif
    }
} // namespace Raytracer
