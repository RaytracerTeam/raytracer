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
        if (key >= sf::Keyboard::Key::Num0 && key <= sf::Keyboard::Key::Num9) {
            int slot = static_cast<int>(key) - static_cast<int>(sf::Keyboard::Key::Num0);
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
