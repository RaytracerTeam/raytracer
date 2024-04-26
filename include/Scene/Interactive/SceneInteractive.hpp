/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteractive.hpp
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Scene/Interactive/CameraInteractive.hpp"

#include <SFML/Graphics.hpp>

namespace Raytracer {
    class SceneInteractive {
    public:
        SceneInteractive(Dimension &dimension, const std::string &title);
        ~SceneInteractive() = default;

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
        void updateDimension(unsigned int width, unsigned int height);

        std::unique_ptr<sf::Uint8[]> RColorToPixelBuffer(const std::vector<Raytracer::Color> &vectorRes);
        void setRColorToImg(const std::vector<Raytracer::Color> &vectorRes);
        void handleEvents(void);
        void displayFramerate(void);

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
    };
} // namespace Raytracer
