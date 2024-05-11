/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** removeSelectedObject
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::removeSelectedObject(void)
    {
        if (m_selectedObject < 0)
            return;
        switch (m_objectSelection) {
        case ObjectSelection::PRIMITIVE:
            m_scene->getPrimitives()[m_selectedObject]->setdieASAP(true);
            // m_scene->removePrimitive(m_selectedObject);
            break;
        case ObjectSelection::LIGHT: {
            SceneLightning &lightSystem = m_scene->getLightSystem();
            size_t localSelectedObject = m_selectedObject;
            if (localSelectedObject < lightSystem.getAmbientLights().size()) {
                lightSystem.getAmbientLights()[localSelectedObject]->setdieASAP(true);
                // lightSystem.removeAmbientLight(localSelectedObject);
                break;
            }
            localSelectedObject -= lightSystem.getAmbientLights().size();
            if (localSelectedObject < lightSystem.getDirectionalLights().size()) {
                lightSystem.getDirectionalLights()[localSelectedObject]->setdieASAP(true);
                // lightSystem.removeDirectionalLight(localSelectedObject);
                break;
            }
            localSelectedObject -= lightSystem.getDirectionalLights().size();
            if (localSelectedObject < lightSystem.getLights().size()) {
                lightSystem.getLights()[localSelectedObject]->setdieASAP(true);
                // lightSystem.removeLight(localSelectedObject);
                break;
            }
            break;
        }
        case ObjectSelection::CAMERA:
            m_scene->removeCamera(m_selectedObject);
            setupCamera();
            break;
        default:
            break;
        }
        m_selectedObject = -1;
        m_updateBVH = true;
        m_needRendering = true;
    }
} // namespace Raytracer
