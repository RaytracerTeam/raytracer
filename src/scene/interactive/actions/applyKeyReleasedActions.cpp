/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** applyKeyReleasedActions
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void SceneInteractive::applyKeyReleasedActions(sf::Keyboard::Key key)
    {
        int i = 0;
        for (auto &action : m_releaseActions) {
            if (action == key) {
                applyKeyReleasedAction((SceneReleaseActions)i);
            }
            i++;
        }
    }

    void SceneInteractive::applyKeyReleasedAction(SceneReleaseActions action)
    {
        switch (action) {
        case SceneReleaseActions::SCREENSHOT: {
            const auto time = std::chrono::system_clock::now().time_since_epoch().count();
            const auto render = m_scene->getRender();
            render.saveToFile(std::string("screenshots/screenshot-")
                + std::to_string(time / 100000) + std::string(".png"));
            break;
        }
        case SceneReleaseActions::RESET: {
            m_interacCam.getCamera()->reset();
            m_needRendering = true;
            break;
        }
        case SceneReleaseActions::EXIT:
            Parsing::saveScene(*m_scene, TEMP_CFG_FILE);
            m_window.close();
            break;
        #ifdef BONUS
        case SceneReleaseActions::SAVE_CURRENT_AND_EXIT:
            if (strcmp(m_loadFileBuf, SCENE_PATH) == 0)
                strcpy(m_loadFileBuf, TEMP_CFG_FILE);
            Parsing::saveScene(*m_scene, m_loadFileBuf);
            m_window.close();
            break;
        case SceneReleaseActions::QUICK_SAVE_AND_EXIT:
            Parsing::saveScene(*m_scene, QUICK_SAVE_CFG_FILE);
            m_window.close();
            break;
        case SceneReleaseActions::SHOW_DEBUG:
            m_showDebug = !m_showDebug;
            break;
        case SceneReleaseActions::TOGGLE_FULLSCREEN:
            m_fullscreen = !m_fullscreen;
            setupImageSize();
            break;
        case SceneReleaseActions::REMOVE_OBJECT:
            removeSelectedObject();
            break;
        #endif
        case SceneReleaseActions::TOGGLE_MOUSE:
            m_useMouse = !m_useMouse;
            if (m_useMouse) {
                m_mousePosBeforeUse = sf::Mouse::getPosition();
                sf::Mouse::setPosition(MOUSE_CENTER);
                m_window.setMouseCursorVisible(false);
                m_mouseCentered = 2;
            } else {
                m_window.setMouseCursorVisible(true);
                sf::Mouse::setPosition(m_mousePosBeforeUse - m_mouseCenterCorrection);
                m_needRendering = true;
            }
            break;
        case SceneReleaseActions::TOGGLE_SIMPLE_MOUSE:
            m_useSimpleMouse = !m_useSimpleMouse;
            m_lastMousePos = sf::Mouse::getPosition();
            break;
        case SceneReleaseActions::SELECT_PRIMITIVE:
            releaseSelectedPrimitive();
            break;
        default:
            break;
        }
    }

} // namespace Raytracer
