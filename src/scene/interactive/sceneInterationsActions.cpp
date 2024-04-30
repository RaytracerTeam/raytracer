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
        m_actions.push_back(std::make_pair(sf::Keyboard::Escape, false));   // EXIT
        m_actions.push_back(std::make_pair(sf::Keyboard::C, false));        // QUICK_SAVE
        m_actions.push_back(std::make_pair(sf::Keyboard::X, false));        // SAVE_AND_QUIT
        m_actions.push_back(std::make_pair(sf::Keyboard::F, false));        // SHOW_FPS
        m_actions.push_back(std::make_pair(sf::Keyboard::Return, false));   // RESET
        parseConfigFile("config/keys.cfg");
    }
    void SceneInteractive::parseConfigFile(const std::string &filename)
    {
        libconfig::Config cfg;
        cfg.readFile(filename.c_str());
        if (!cfg.exists("keys")) {
            std::cerr << "No keys found in config file" << std::endl;
            return;
        }
        int i = -1;
        for (auto &key : cfg.lookup("keys")) {
            i++;
            std::string keyCode = key.lookup("key");
            std::transform(keyCode.begin(), keyCode.end(), keyCode.begin(), ::toupper);
            sf::Keyboard::Key sfKey = sf::Keyboard::Key::Unknown;
            if (keyCode == "UP")
                sfKey = sf::Keyboard::Key::Up;
            else if (keyCode == "DOWN")
                sfKey = sf::Keyboard::Key::Down;
            else if (keyCode == "LEFT")
                sfKey = sf::Keyboard::Key::Left;
            else if (keyCode == "RIGHT")
                sfKey = sf::Keyboard::Key::Right;
            else if (keyCode == "SPACE")
                sfKey = sf::Keyboard::Key::Space;
            else if (keyCode == "LSHIFT")
                sfKey = sf::Keyboard::Key::LShift;
            else if (keyCode == "LCTRL")
                sfKey = sf::Keyboard::Key::LControl;
            else if (keyCode == "ENTER")
                sfKey = sf::Keyboard::Key::Return;
            else if (keyCode == "ESCAPE")
                sfKey = sf::Keyboard::Key::Escape;
            else if (keyCode == "F3")
                sfKey = sf::Keyboard::Key::F3;
            else if (keyCode >= "A" && keyCode <= "Z")
                sfKey = (sf::Keyboard::Key)(sf::Keyboard::A + keyCode[0] - 'A');
            else {
                throw std::invalid_argument("Invalid key name: " + keyCode);
                continue;
            }
            m_actions[i].first = sfKey;
        }
    }

    void SceneInteractive::applyAction(SceneAction action)
    {
        Camera *camera = m_interacCam.getCamera();
        auto camPos = camera->getPos();
        auto camAngle = camera->getAngle();
        auto movementCamAngle = camAngle;
        movementCamAngle.setPitch(0);
        m_needRendering = true;

        if (m_actions[SceneAction::MOVE_FORWARD].second) {
            camPos += Math::Vector3D(0, 0, -m_movementSpeed).rotate(movementCamAngle);
        }
        if (m_actions[SceneAction::MOVE_BACKWARD].second) {
            camPos += Math::Vector3D(0, 0, m_movementSpeed).rotate(movementCamAngle);
        }
        if (m_actions[SceneAction::MOVE_LEFT].second) {
            camPos += Math::Vector3D(-m_movementSpeed, 0, 0).rotate(movementCamAngle);
        }
        if (m_actions[SceneAction::MOVE_RIGHT].second) {
            camPos += Math::Vector3D(m_movementSpeed, 0, 0).rotate(movementCamAngle);
        }
        if (m_actions[SceneAction::MOVE_UP].second) {
            camPos += Math::Vector3D(0, m_movementSpeed, 0);
        }
        if (m_actions[SceneAction::MOVE_DOWN].second) {
            camPos += Math::Vector3D(0, -m_movementSpeed, 0);
        }
        if (m_actions[SceneAction::ROTATE_UP].second) {
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() + m_rotationSpeed, -90., 90.));
            camera->setAngle(camAngle);
        }
        if (m_actions[SceneAction::ROTATE_DOWN].second) {
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() - m_rotationSpeed, -90., 90.));
            camera->setAngle(camAngle);
        }
        if (m_actions[SceneAction::ROTATE_LEFT].second) {
            camAngle.setYaw(camAngle.getYaw() + m_rotationSpeed);
            camera->setAngle(camAngle);
        }
        if (m_actions[SceneAction::ROTATE_RIGHT].second) {
            camAngle.setYaw(camAngle.getYaw() - m_rotationSpeed);
            camera->setAngle(camAngle);
        }
        if (m_actions[SceneAction::SPRINT].second) {
            m_movementSpeed = DEFAULT_MOVEMENT_SPEED * 4;
        } else {
            m_movementSpeed = DEFAULT_MOVEMENT_SPEED;
        }
        camera->setPos(camPos);
        if (m_actions[SceneAction::RESET].second) {
            camera->reset();
        }
        if (m_actions[SceneAction::EXIT].second) {
            m_window.close();
        }
        if (m_actions[SceneAction::QUICK_SAVE].second) {
            Parsing::saveScene(*m_scene, "scenes/quick_save.cfg");
        }
        if (m_actions[SceneAction::SAVE_AND_EXIT].second) {
            Parsing::saveScene(*m_scene, "scenes/quick_save.cfg");
            m_window.close();
        }
        if (m_actions[SceneAction::SHOW_FPS].second) {
            m_showFps = !m_showFps;
        }
    }

    void SceneInteractive::applyActions(void)
    {
        int i = 0;
        for (auto &action : m_actions) {
            if (action.second)
                applyAction((SceneAction)i);
            i++;
        }
    }
} // namespace Raytracer
