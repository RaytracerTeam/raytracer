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

namespace Raytracer {
    bool CameraInteractive::updatePos(sf::Keyboard::Key code)
    {
        auto camPos = m_camera->getPos();
        auto camAngle = m_camera->getAngle();
        auto movementCamAngle = camAngle;
        movementCamAngle.setPitch(0);

        switch (code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::Z:
            camPos += Math::Vector3D(0, 0, -1).rotate(movementCamAngle);
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            camPos += Math::Vector3D(0, 0, 1).rotate(movementCamAngle);
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::Q:
            camPos += Math::Vector3D(-1, 0, 0).rotate(movementCamAngle);
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            camPos += Math::Vector3D(1, 0, 0).rotate(movementCamAngle);
            break;
        case sf::Keyboard::Space:
        case sf::Keyboard::PageUp:
        case sf::Keyboard::A:
            camPos += Math::Vector3D(0, 1, 0);
            break;
        case sf::Keyboard::LShift:
        case sf::Keyboard::PageDown:
        case sf::Keyboard::E:
            camPos += Math::Vector3D(0, -1, 0);
            break;
        case sf::Keyboard::U:
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() + 10, -90., 90.));
            m_camera->setAngle(camAngle);
            break;
        case sf::Keyboard::J:
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() - 10, -90., 90.));
            m_camera->setAngle(camAngle);
            break;
        case sf::Keyboard::H:
            camAngle.setYaw(camAngle.getYaw() + 10);
            m_camera->setAngle(camAngle);
            break;
        case sf::Keyboard::K:
            camAngle.setYaw(camAngle.getYaw() - 10);
            m_camera->setAngle(camAngle);
            break;
        default:
            return false;
        }
        m_camera->setPos(camPos);
        return true;
    }

    bool CameraInteractive::handleInput(const sf::Event &event, sf::Window &window)
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
        case sf::Event::KeyPressed:
            return updatePos(event.key.code);
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
