/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** CameraInteractive.hpp
*/

#pragma once

#include "Scene/Camera.hpp"
#include "Scene/Interactive/SceneAction.hpp"

#include <SFML/Graphics.hpp>

namespace Raytracer {
    /* This class wraps the current camera */
    class CameraInteractive {
    public:
        CameraInteractive() = default;
        CameraInteractive(Camera *camera) : m_camera(camera) {};
        ~CameraInteractive() = default;

        void setCamera(Camera *camera) { m_camera = camera; }

        Camera *getCamera(void) const { return m_camera; }

        bool handleInput(const sf::Event &event, sf::Window &window, std::vector<std::pair<sf::Keyboard::Key, bool>> &actions);

    private:
        void updatePos(SceneAction action);
        bool applyKeyToActions(std::vector<std::pair<sf::Keyboard::Key, bool>> &actions, sf::Keyboard::Key key, bool isPressed);
        void applyActions(void);
        //////////////

        Camera *m_camera = nullptr;
    };
} // namespace Raytracer
