/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteractive.hpp
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Scene/Interactive/CameraInteractive.hpp"

#include "Scene/Primitives/Plane.hpp"
#include "Scene/Primitives/Sphere.hpp"

#ifdef BONUS
    #include "imgui.h"
    #include "imgui-SFML.h"
#endif

#include <SFML/Graphics.hpp>

namespace Raytracer {
    #define DEFAULT_MOVEMENT_SPEED 0.3f
    #define DEFAULT_ROTATION_SPEED 3
    #define SCREEN_RATIO 16.0f / 9.0f
    #define FILE_BUF_SIZE 20

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
        void applyAction(SceneAction action);
        void applyActions(void);

        void updateDimension(unsigned int width, unsigned int height);

        std::unique_ptr<sf::Uint8[]> RColorToPixelBuffer(const std::vector<Raytracer::Color> &vectorRes);
        void setRColorToImg(const std::vector<Raytracer::Color> &vectorRes);
        void handleEvents(void);
        void displayFramerate(void);

        // ImGui
        void handleImGui();
        void editSphere(Sphere *sphere);
        void editPlane(Plane *plane);

        /////////////////////////////////

        // TODO utiliser shared ptr
        Scene *m_scene = nullptr;
        CameraInteractive m_interacCam;

        Dimension &m_dimension;
        sf::RenderWindow m_window;
        sf::Image m_img;
        sf::Texture m_texture;

        sf::Clock m_clock;
        sf::Time m_currentTime;
        sf::Time m_previousTime;
    
        // ImGui
        sf::Clock m_deltaClock;
        int m_renderResolution = 400;
        char m_fileBuf[FILE_BUF_SIZE];
        bool m_isWriting = false;
        bool m_showFps = false;

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
