/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** CameraInteractive.cpp
*/

#include "Scene/Interactive/CameraInteractive.hpp"
#include "Math/Algorithm.hpp"

#include <cmath>

// temp
#include <iostream>
#include <libconfig.h++>

namespace Raytracer {
    bool CameraInteractive::applyKeyToActions(std::vector<std::pair<sf::Keyboard::Key, bool>> &actions, sf::Keyboard::Key key, bool isPressed)
    {
        if (m_camera == nullptr)
            return false;

        for (auto &action : actions) {
            if (action.first == key) {
                action.second = isPressed;
                return true;
            }
        }
        return false;
    }

    bool CameraInteractive::handleInput(const sf::Event &event, std::vector<std::pair<sf::Keyboard::Key, bool>> &actions)
    {
        if (m_camera == nullptr)
            return false;

        switch (event.type) {
        case sf::Event::KeyReleased:
            return applyKeyToActions(actions, event.key.code, false);
        case sf::Event::KeyPressed:
            return applyKeyToActions(actions, event.key.code, true);
        default:
            return false;
        }
        return false;
    }
} // namespace Raytracer
