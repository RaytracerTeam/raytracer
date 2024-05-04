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
        if (m_selectedObject <= 0)
            return;
        m_selectedObject--;
        switch (m_objectSelection) {
        case ObjectSelection::PRIMITIVE: m_scene->removePrimitive(m_selectedObject); break;
        case ObjectSelection::LIGHT: m_scene->removeLight(m_selectedObject); break;
        case ObjectSelection::CAMERA: m_scene->removeCamera(m_selectedObject);
        default:
            break;
        }
        m_selectedObject = 0;
        m_needRendering = true;
    }
} // namespace Raytracer
