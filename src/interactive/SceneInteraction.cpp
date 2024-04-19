/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteraction.cpp
*/

#include "Interactive/CameraInteractive.hpp"
#include "Interactive/SceneInteractive.hpp"

// temp : add fps
// #include <cmath>
// #include <iostream>
// float fps;
// sf::Clock clock = sf::Clock();
// sf::Time previousTime = clock.getElapsedTime();
// sf::Time currentTime;
// currentTime = clock.getElapsedTime();
// fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
// std::cout << "fps =" << std::floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
// previousTime = currentTime;

namespace Raytracer {
    SceneInteractive::SceneInteractive(Dimension &dimension, const std::string &title)
        : m_dimension(dimension)
        , m_window(sf::VideoMode(dimension.getWidth(), dimension.getHeight()), title)
    {
        m_texture.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_img.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_window.setFramerateLimit(24);
    }

    void SceneInteractive::updateDimension(unsigned int width, unsigned int height)
    {
        m_dimension.setWidth(width);
        m_dimension.setHeight(height);
        m_texture.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_img.create(m_dimension.getWidth(), m_dimension.getHeight());
    }

    void SceneInteractive::handleEvents(void)
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);

                updateDimension(event.size.width, event.size.height);
                m_window.setView(sf::View(visibleArea));
            }
            if (m_interacCam.handleInput(event, m_window))
                return;
            if (m_interacCam.isActiveMouse())
                m_interacCam.handleMouse(event, m_window);
        }
    }

    void SceneInteractive::setScene(Scene *scene)
    {
        m_scene = scene;
        m_interacCam.setCamera(scene->getCurrentCamera());
    }

    void SceneInteractive::loop(void)
    {
        while (m_window.isOpen()) {
            handleEvents();

            auto pixels = RColorToPixelBuffer(m_scene->render());
            m_img.create(m_dimension.getWidth(), m_dimension.getHeightD(), pixels.get());

            m_texture.update(m_img);
            m_window.clear();
            m_window.draw(sf::Sprite(m_texture));
            m_window.display();
        }
    }

    ///////////////////////////

    std::unique_ptr<sf::Uint8[]> SceneInteractive::RColorToPixelBuffer(const std::vector<Raytracer::Color> &vectorRes)
    {
        sf::Uint8 *pixels = new sf::Uint8[m_dimension.getSize() * 4];
        for (size_t i = 0; const auto &value : vectorRes) {
            pixels[i++] = Color::PercentToRGB(value.getR());
            pixels[i++] = Color::PercentToRGB(value.getG());
            pixels[i++] = Color::PercentToRGB(value.getB());
            pixels[i++] = 255;
        }
        return std::unique_ptr<sf::Uint8[]>(pixels);
    }

} // namespace Raytracer
