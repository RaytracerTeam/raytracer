/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** applyKeyPressedActions
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::applyKeyPressedActions(sf::Keyboard::Key key)
    {
        int i = 0;
        for (auto &action : m_releaseActions) {
            if (action == key) {
                applyKeyPressedAction((SceneReleaseActions)i);
            }
            i++;
        }
        if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
            int slot = key - sf::Keyboard::Num0 - 1;
            m_scene->getInventory().setCurrentMaterialIndex(slot);
            #ifdef BONUS
            if (m_objectSelection == ObjectSelection::INVENTORY)
                m_selectedObject = slot;
            #endif
        }
    }

    void SceneInteractive::applyKeyPressedAction(SceneReleaseActions action)
    {
        switch (action) {
        case SceneReleaseActions::SELECT_PRIMITIVE:
            selectShootedPrimitive();
            break;
        default:
            break;
        }
    }
} // namespace Raytracer
