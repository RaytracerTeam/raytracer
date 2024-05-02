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

    bool CameraInteractive::handleInput(const sf::Event &event, sf::Window &window, std::vector<std::pair<sf::Keyboard::Key, bool>> &actions)
    {
        if (m_camera == nullptr)
            return false;

        switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Right) {
                window.setMouseCursorVisible(false);
                m_mouseStillPressed = true;
                resetPosMouse(window);
                return true;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right) {
                window.setMouseCursorVisible(true);
                m_mouseStillPressed = false;
                return true;
            }
            break;
        case sf::Event::KeyReleased:
            return applyKeyToActions(actions, event.key.code, false);
        case sf::Event::KeyPressed:
            return applyKeyToActions(actions, event.key.code, true);
        default:
            return false;
        }
        return false;
    }

    /* Todo : implement quaternion for giving the correct mouse movement */
    void CameraInteractive::handleMouse(const sf::Event &event, const sf::Window &window)
    {
        static double sensivity = 0.03;

        if (m_camera == nullptr)
            return;
        auto mousePos = Math::Vector3D(event.mouseButton.button, event.mouseButton.x);
        auto refPos = Math::Vector3D((double)window.getSize().x / 2., (double)window.getSize().y / 2.);
        auto delta = refPos - mousePos;

        if (delta.getX() == 0 && delta.getY() == 0)
            return;
        auto angle = m_camera->getAngle();
        angle.setYaw(angle.getYaw() + delta.getX() * sensivity);
        angle.setPitch(Math::Algorithm::clampD(angle.getPitch() + delta.getY() * sensivity, -90., 90.));
        m_camera->setAngle(angle);
        resetPosMouse(window);
    }
} // namespace Raytracer
