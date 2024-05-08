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
        case ObjectSelection::PRIMITIVE: m_scene->removePrimitive(m_selectedObject); break;
        case ObjectSelection::LIGHT: m_scene->removeLight(m_selectedObject); break;
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
