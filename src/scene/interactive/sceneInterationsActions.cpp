/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** sceneInterationsActions
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Math/Algorithm.hpp"
#include "Parsing/Parsing.hpp"

#include <iostream>
#include <libconfig.h++>

namespace Raytracer
{
    void SceneInteractive::resetActions(void)
    {
        for (auto &action : m_actions) {
            action.second = false;
        }
    }

    void SceneInteractive::setupActions(void)
    {
        m_actions.push_back(std::make_pair(sf::Keyboard::Up, false));       // MOVE_FORWARD
        m_actions.push_back(std::make_pair(sf::Keyboard::Down, false));     // MOVE_BACKWARD
        m_actions.push_back(std::make_pair(sf::Keyboard::Left, false));     // MOVE_LEFT
        m_actions.push_back(std::make_pair(sf::Keyboard::Right, false));    // MOVE_RIGHT
        m_actions.push_back(std::make_pair(sf::Keyboard::Space, false));    // MOVE_UP
        m_actions.push_back(std::make_pair(sf::Keyboard::LShift, false));   // MOVE_DOWN
        m_actions.push_back(std::make_pair(sf::Keyboard::U, false));        // ROTATE_UP
        m_actions.push_back(std::make_pair(sf::Keyboard::J, false));        // ROTATE_DOWN
        m_actions.push_back(std::make_pair(sf::Keyboard::H, false));        // ROTATE_LEFT
        m_actions.push_back(std::make_pair(sf::Keyboard::K, false));        // ROTATE_RIGHT
        m_actions.push_back(std::make_pair(sf::Keyboard::LControl, false)); // SPRINT

        m_releaseActions.push_back(sf::Keyboard::Escape);          // EXIT
        m_releaseActions.push_back(sf::Keyboard::C);               // SAVE_CURRENT_AND_EXIT
        m_releaseActions.push_back(sf::Keyboard::X);               // SAVE_AND_QUIT
        m_releaseActions.push_back(sf::Keyboard::F3);              // SHOW_DEBUG
        m_releaseActions.push_back(sf::Keyboard::F2);              // SCREENSHOT
        m_releaseActions.push_back(sf::Keyboard::Backspace);       // REMOVE_OBJECT
        m_releaseActions.push_back(sf::Keyboard::F11);             // TOGGLE_FULLSCREEN
        m_releaseActions.push_back(sf::Keyboard::M);               // TOGGLE_MOUSE
        m_releaseActions.push_back(sf::Keyboard::N);               // TOGGLE_SIMPLE_MOUSE
        m_releaseActions.push_back(sf::Keyboard::O);          // RESET
        parseConfigFile("config/keys.cfg");
    }

    static sf::Keyboard::Key getSFMLKey(const std::string &keyCode)
    {
        if (keyCode == "UP")
                return sf::Keyboard::Key::Up;
            else if (keyCode == "DOWN")
                return sf::Keyboard::Key::Down;
            else if (keyCode == "LEFT")
                return sf::Keyboard::Key::Left;
            else if (keyCode == "RIGHT")
                return sf::Keyboard::Key::Right;
            else if (keyCode == "SPACE")
                return sf::Keyboard::Key::Space;
            else if (keyCode == "LSHIFT")
                return sf::Keyboard::Key::LShift;
            else if (keyCode == "LCTRL")
                return sf::Keyboard::Key::LControl;
            else if (keyCode == "ESCAPE")
                return sf::Keyboard::Key::Escape;
            else if (keyCode == "F2")
                return sf::Keyboard::Key::F2;
            else if (keyCode == "F3")
                return sf::Keyboard::Key::F3;
            else if (keyCode == "F11")
                return sf::Keyboard::F11;
            else if (keyCode == "BACKSPACE")
                return sf::Keyboard::Key::Backspace;
            else if (keyCode == "TAB")
                return sf::Keyboard::Key::Tab;
            else if (keyCode >= "A" && keyCode <= "Z")
                return (sf::Keyboard::Key)(sf::Keyboard::A + keyCode[0] - 'A');
            else {
                throw std::invalid_argument("keys.cfg: Invalid key name: " + keyCode);
            }
    }

    static SceneAction getSceneActionIndex(std::string action)
    {
        std::transform(action.begin(), action.end(), action.begin(), ::toupper);
        if (action == "MOVE_FORWARD")
            return SceneAction::MOVE_FORWARD;
        else if (action == "MOVE_BACKWARD")
            return SceneAction::MOVE_BACKWARD;
        else if (action == "MOVE_LEFT")
            return SceneAction::MOVE_LEFT;
        else if (action == "MOVE_RIGHT")
            return SceneAction::MOVE_RIGHT;
        else if (action == "MOVE_UP")
            return SceneAction::MOVE_UP;
        else if (action == "MOVE_DOWN")
            return SceneAction::MOVE_DOWN;
        else if (action == "ROTATE_UP")
            return SceneAction::ROTATE_UP;
        else if (action == "ROTATE_DOWN")
            return SceneAction::ROTATE_DOWN;
        else if (action == "ROTATE_LEFT")
            return SceneAction::ROTATE_LEFT;
        else if (action == "ROTATE_RIGHT")
            return SceneAction::ROTATE_RIGHT;
        else if (action == "SPRINT")
            return SceneAction::SPRINT;
        else
            throw std::invalid_argument("keys.cfg: Invalid action name: " + action);
    }

    static SceneReleaseActions getSceneReleaseActionIndex(std::string action)
    {
        std::transform(action.begin(), action.end(), action.begin(), ::toupper);
        if (action == "EXIT")
            return SceneReleaseActions::EXIT;
        else if (action == "SAVE_CURRENT_AND_EXIT")
            return SceneReleaseActions::SAVE_CURRENT_AND_EXIT;
        else if (action == "QUICK_SAVE_AND_EXIT")
            return SceneReleaseActions::QUICK_SAVE_AND_EXIT;
        else if (action == "SHOW_DEBUG")
            return SceneReleaseActions::SHOW_DEBUG;
        else if (action == "SCREENSHOT")
            return SceneReleaseActions::SCREENSHOT;
        else if (action == "REMOVE_OBJECT")
            return SceneReleaseActions::REMOVE_OBJECT;
        else if (action == "TOGGLE_FULLSCREEN")
            return SceneReleaseActions::TOGGLE_FULLSCREEN;
        else if (action == "TOGGLE_MOUSE")
            return SceneReleaseActions::TOGGLE_MOUSE;
        else if (action == "TOGGLE_SIMPLE_MOUSE")
            return SceneReleaseActions::TOGGLE_SIMPLE_MOUSE;
        else if (action == "RESET")
            return SceneReleaseActions::RESET;
        else
            throw std::invalid_argument("keys.cfg: Invalid action name: " + action);
    }

    void SceneInteractive::parseConfigFile(const std::string &filename)
    {
        if (!std::filesystem::exists(filename)) {
            if (!std::filesystem::exists("config/keys_example.cfg"))
                throw std::invalid_argument("config/keys.cfg doesn't exists and config/keys_example.cfg is not found");
            std::filesystem::copy("config/keys_example.cfg", filename);
        }
        libconfig::Config cfg;
        cfg.readFile(filename.c_str());
        if (!cfg.exists("keys")) {
            std::cerr << "No 'keys' found in config file" << std::endl;
            return;
        }
        for (auto &key : cfg.lookup("keys")) {
            std::string keyCode = key.lookup("key");
            std::transform(keyCode.begin(), keyCode.end(), keyCode.begin(), ::toupper);
            sf::Keyboard::Key sfKey = getSFMLKey(keyCode);
            SceneAction action = getSceneActionIndex(key.lookup("name"));
            m_actions[action].first = sfKey;
        }
        if (!cfg.exists("onReleaseKeys")) {
            std::cerr << "No 'onReleaseKeys' found in config file" << std::endl;
            return;
        }
        for (auto &key : cfg.lookup("onReleaseKeys")) {
            std::string keyCode = key.lookup("key");
            std::transform(keyCode.begin(), keyCode.end(), keyCode.begin(), ::toupper);
            sf::Keyboard::Key sfKey = getSFMLKey(keyCode);
            SceneReleaseActions action = getSceneReleaseActionIndex(key.lookup("name"));
            m_releaseActions[action] = sfKey;
        }
    }

    void SceneInteractive::applyActions(void)
    {
        Camera *camera = m_interacCam.getCamera();
        auto camPos = camera->getPos();
        auto camAngle = camera->getAngle();
        auto movementCamAngle = camAngle;
        movementCamAngle.setPitch(0);

        if (m_actions[SceneAction::MOVE_FORWARD].second) {
            camPos += Math::Vector3D(0, 0, -m_movementSpeed).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_BACKWARD].second) {
            camPos += Math::Vector3D(0, 0, m_movementSpeed).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_LEFT].second) {
            camPos += Math::Vector3D(-m_movementSpeed, 0, 0).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_RIGHT].second) {
            camPos += Math::Vector3D(m_movementSpeed, 0, 0).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_UP].second) {
            camPos += Math::Vector3D(0, m_movementSpeed, 0);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_DOWN].second) {
            camPos += Math::Vector3D(0, -m_movementSpeed, 0);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_UP].second) {
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() + m_rotationSpeed, -90., 90.));
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_DOWN].second) {
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() - m_rotationSpeed, -90., 90.));
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_LEFT].second) {
            camAngle.setYaw(camAngle.getYaw() + m_rotationSpeed);
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_RIGHT].second) {
            camAngle.setYaw(camAngle.getYaw() - m_rotationSpeed);
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::SPRINT].second) {
            m_movementSpeed = m_defaultMovementSpeed * 4;
        } else {
            m_movementSpeed = m_defaultMovementSpeed;
        }
        camera->setPos(camPos);
    }

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
             m_img.saveToFile(std::string("screenshots/screenshot-")
                + std::to_string(time / 100000) + std::string(".png"));
            break;
        }
        case SceneReleaseActions::RESET: {
            m_interacCam.getCamera()->reset();
            m_needRendering = true;
            break;
        }
        case SceneReleaseActions::EXIT:
            m_window.close();
            break;
        case SceneReleaseActions::SAVE_CURRENT_AND_EXIT:
            Parsing::saveScene(*m_scene, m_loadFileBuf);
            m_window.close();
            break;
        case SceneReleaseActions::QUICK_SAVE_AND_EXIT:
            Parsing::saveScene(*m_scene, "scenes/quick_save.cfg");
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
            }
            break;
        case SceneReleaseActions::TOGGLE_SIMPLE_MOUSE:
            m_useSimpleMouse = !m_useSimpleMouse;
            m_lastMousePos = sf::Mouse::getPosition();
            break;
        default:
            break;
        }
    }

    void SceneInteractive::handleMouse(void)
    {
        Camera &currentCamera = m_scene->getCurrentCamera();

        float sensivity = m_rotationSpeed / 10;

        if (m_useSimpleMouse) {
            auto pos = sf::Mouse::getPosition();
            auto delta = pos - m_lastMousePos;
            if (delta.x == 0 && delta.y == 0)
                return;
            auto angle = currentCamera.getAngle();
            angle.setYaw(angle.getYaw() - delta.x * sensivity);
            angle.setPitch(Math::Algorithm::clampD(angle.getPitch() - delta.y * sensivity, -90., 90.));
            currentCamera.setAngle(angle);
            m_needRendering = true;
            m_lastMousePos = pos;
        }

        else if (m_useMouse) {
            if (m_mouseCentered > 1) {
                m_mouseCentered--;
                return;
            }
            if (m_mouseCentered == 1) {
                m_mouseCenterCorrection = sf::Mouse::getPosition() - MOUSE_CENTER;
                m_mouseCentered = 0;
            }

            auto pos = sf::Mouse::getPosition();
            auto delta = pos - MOUSE_CENTER;
            delta -= m_mouseCenterCorrection;
            if (delta.x == 0 && delta.y == 0)
                return;
            sf::Mouse::setPosition(MOUSE_CENTER);
            auto angle = currentCamera.getAngle();
            angle.setYaw(angle.getYaw() - delta.x * sensivity);
            angle.setPitch(Math::Algorithm::clampD(angle.getPitch() - delta.y * sensivity, -90., 90.));
            currentCamera.setAngle(angle);
            m_needRendering = true;
        }
    }
} // namespace Raytracer
