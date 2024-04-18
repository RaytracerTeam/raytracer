/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** CameraInteractive.hpp
*/

#pragma once

#include "Camera.hpp"

#include <SFML/Graphics.hpp>

namespace Raytracer {
    /* This class wraps the current camera */
    class CameraInteractive {
    public:
        CameraInteractive() = default;
        CameraInteractive(Camera *camera)
            : m_camera(camera) {};
        ~CameraInteractive() = default;

        void setCamera(Camera *camera)
        {
            m_camera = camera;
        }

        bool handleInput(const sf::Event &event, sf::Window &window);
        void handleMouse(const sf::Event &event, const sf::Window &window);

        bool isActiveMouse(void) const { return m_mouseStillPressed; }

    private:
        bool updatePos(sf::Keyboard::Key code);
        static inline void resetPosMouse(const sf::Window &window)
        {
            sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
        }

        //////////////

        Camera *m_camera = nullptr;
        bool m_mouseStillPressed = false;
    };
} // namespace Raytracer
