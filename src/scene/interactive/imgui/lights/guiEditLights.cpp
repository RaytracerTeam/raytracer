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
        SceneLightning &lightSystem = m_scene->getLightSystem();
        ILight *light = nullptr;
        if ((size_t)m_selectedObject < lightSystem.getLights().size())
            light = lightSystem.getLights()[m_selectedObject].get();
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
        DEFAULT_INTENSITY_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            light->setIntensity(intensity);
            m_needRendering = true;
        }

        customEditLights(light);

        #endif
    }
} // namespace Raytracer
