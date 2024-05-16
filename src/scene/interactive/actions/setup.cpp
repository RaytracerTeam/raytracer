/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** setup
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Math/Algorithm.hpp"
#include "Parsing/Parsing.hpp"

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
        m_actions.push_back(std::make_pair(sf::Keyboard::R, false));        // PAINT

        m_releaseActions.push_back(sf::Keyboard::Escape);          // EXIT
        m_releaseActions.push_back(sf::Keyboard::C);               // SAVE_CURRENT_AND_EXIT
        m_releaseActions.push_back(sf::Keyboard::X);               // SAVE_AND_QUIT
        m_releaseActions.push_back(sf::Keyboard::F3);              // SHOW_DEBUG
        m_releaseActions.push_back(sf::Keyboard::F2);              // SCREENSHOT
        m_releaseActions.push_back(sf::Keyboard::Delete);          // REMOVE_OBJECT
        m_releaseActions.push_back(sf::Keyboard::F11);             // TOGGLE_FULLSCREEN
        m_releaseActions.push_back(sf::Keyboard::M);               // TOGGLE_MOUSE
        m_releaseActions.push_back(sf::Keyboard::N);               // TOGGLE_SIMPLE_MOUSE
        m_releaseActions.push_back(sf::Keyboard::O);               // RESET
        m_releaseActions.push_back(sf::Keyboard::G);               // SELECT_PRIMITIVE
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
            else if (keyCode == "DELETE")
                return sf::Keyboard::Key::Delete;
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
        else if (action == "PAINT")
            return SceneAction::PAINT;
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
        else if (action == "SELECT_PRIMITIVE")
            return SceneReleaseActions::SELECT_PRIMITIVE;
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
} // namespace Raytracer
