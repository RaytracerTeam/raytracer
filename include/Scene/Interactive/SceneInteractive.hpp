/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteractive.hpp
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Scene/Interactive/CameraInteractive.hpp"

#ifdef BONUS
    #include "imgui.h"
    #include "imgui-SFML.h"
#endif

#include <SFML/Graphics.hpp>

namespace Raytracer {
    #define DEFAULT_MOVEMENT_SPEED 0.3f
    #define DEFAULT_ROTATION_SPEED 3

    class SceneInteractive {
    public:
        SceneInteractive(Dimension &dimension, const std::string &title);
        ~SceneInteractive();

        void loop(void);

        void setScene(Scene *scene);

        static inline sf::Color RColorToSFColor(const Color &color)
        {
            return sf::Color(
                Color::PercentToRGB(color.getR()),
                Color::PercentToRGB(color.getG()),
                Color::PercentToRGB(color.getB()));
        }

    private:
        void setupActions(void);
        void parseConfigFile(const std::string &filename);
        void updatePos(SceneAction action);
        void applyActions(void);

        void updateDimension(unsigned int width, unsigned int height);

        std::unique_ptr<sf::Uint8[]> RColorToPixelBuffer(const std::vector<Raytracer::Color> &vectorRes);
        void setRColorToImg(const std::vector<Raytracer::Color> &vectorRes);
        void handleEvents(void);
        void handleImGui(float *spherePos, float *sphereColor);

        /////////////////////////////////

        Scene *m_scene = nullptr;
        CameraInteractive m_interacCam;

        Dimension &m_dimension;
        sf::RenderWindow m_window;
        sf::Image m_img;
        sf::Texture m_texture;

        // ImGui
        sf::Clock m_deltaClock;

        // Storing the result of the render
        std::unique_ptr<sf::Uint8 []> m_lastRender;

        // Actions
        std::vector<std::pair<sf::Keyboard::Key, bool>> m_actions;
        bool m_newEvent = true;
        bool m_needRendering = true;
        float m_movementSpeed = DEFAULT_MOVEMENT_SPEED;
        float m_rotationSpeed = DEFAULT_ROTATION_SPEED;
    };
} // namespace Raytracer
