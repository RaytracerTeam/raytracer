/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** sceneInterationsActions
*/

#include "Scene/Interactive/SceneInteractive.hpp"

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
        parseConfigFile("config/keys.cfg");
        // for (auto &action : m_actions) {
        //     std::cout << "Key: " << action.first << std::endl;
        // }
        // std::cout << "W " << sf::Keyboard::W <<
        //     " A " << sf::Keyboard::A <<
        //     " S " << sf::Keyboard::S <<
        //     " D " << sf::Keyboard::D <<
        //     std::endl;
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
            else if (keyCode >= "A" && keyCode <= "Z")
                sfKey = (sf::Keyboard::Key)(sf::Keyboard::A + keyCode[0] - 'A');
            else {
                std::cerr << "Invalid key name: " << keyCode << std::endl;
                continue;
            }
            m_actions[i].first = sfKey;
        }
    }

    void SceneInteractive::updatePos(SceneAction action)
    {
        (void)action;
        return;
    }
    // {
    //     auto camPos = m_camera->getPos();
    //     auto camAngle = m_camera->getAngle();
    //     auto movementCamAngle = camAngle;
    //     movementCamAngle.setPitch(0);

    //     switch (action) {
    //     case sf::Keyboard::Up:
    //     case sf::Keyboard::Z:
    //         camPos += Math::Vector3D(0, 0, -1).rotate(movementCamAngle);
    //         break;
    //     case sf::Keyboard::Down:
    //     case sf::Keyboard::S:
    //         camPos += Math::Vector3D(0, 0, 1).rotate(movementCamAngle);
    //         break;
    //     case sf::Keyboard::Left:
    //     case sf::Keyboard::Q:
    //         camPos += Math::Vector3D(-1, 0, 0).rotate(movementCamAngle);
    //         break;
    //     case sf::Keyboard::Right:
    //     case sf::Keyboard::D:
    //         camPos += Math::Vector3D(1, 0, 0).rotate(movementCamAngle);
    //         break;
    //     case sf::Keyboard::Space:
    //     case sf::Keyboard::PageUp:
    //     case sf::Keyboard::A:
    //         camPos += Math::Vector3D(0, 1, 0);
    //         break;
    //     case sf::Keyboard::LShift:
    //     case sf::Keyboard::PageDown:
    //     case sf::Keyboard::E:
    //         camPos += Math::Vector3D(0, -1, 0);
    //         break;
    //     case sf::Keyboard::U:
    //         camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() + 10, -90., 90.));
    //         m_camera->setAngle(camAngle);
    //         break;
    //     case sf::Keyboard::J:
    //         camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() - 10, -90., 90.));
    //         m_camera->setAngle(camAngle);
    //         break;
    //     case sf::Keyboard::H:
    //         camAngle.setYaw(camAngle.getYaw() + 10);
    //         m_camera->setAngle(camAngle);
    //         break;
    //     case sf::Keyboard::K:
    //         camAngle.setYaw(camAngle.getYaw() - 10);
    //         m_camera->setAngle(camAngle);
    //         break;
    //     default:
    //         throw std::runtime_error("Invalid action");
    //     }
    //     m_camera->setPos(camPos);
    // }

    void SceneInteractive::applyActions(void)
    {
        int i = 0;
        for (auto &action : m_actions) {
            if (action.second) {
                std::cout << "Action: " << i << " " << action.first << std::endl;
                updatePos((SceneAction)i);
            }
            i++;
        }
    }

} // namespace Raytracer
