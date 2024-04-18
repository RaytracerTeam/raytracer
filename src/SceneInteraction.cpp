/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteraction.cpp
*/

#include "SceneInteractive.hpp"

#include <iostream> // temp

namespace Raytracer {
    SceneInteractive::SceneInteractive(Dimension &dimension, const std::string &title)
        : m_dimension(dimension)
        , m_window(sf::VideoMode(dimension.getWidth(), dimension.getHeight()), title)
    {
        m_texture.create(dimension.getWidth(), dimension.getHeight());
        m_img.create(dimension.getWidth(), dimension.getHeight());
        m_window.setFramerateLimit(10);
    }

    void SceneInteractive::handleEvents(void)
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A) {
                    std::cout << "ed" << std::endl;
                }
            }
        }
    }

    void SceneInteractive::loop(void)
    {
        while (m_window.isOpen()) {
            handleEvents();

            auto pixels = RColorToPixelBuffer(m_scene->render());
            m_img.create(m_dimension.getWidth(), m_dimension.getHeightD(), pixels.get());
            // setRColorToImg(m_scene->render());

            m_texture.update(m_img);
            m_window.clear();
            m_window.draw(sf::Sprite(m_texture));
            m_window.display();
        }
    }

    ///////////////////////////

    std::unique_ptr<sf::Uint8> SceneInteractive::RColorToPixelBuffer(const std::vector<Raytracer::Color> &vectorRes)
    {
        sf::Uint8 *pixels = new sf::Uint8[m_dimension.getSize() * 4];
        for (size_t i = 0; const auto &value : vectorRes) {
            pixels[i++] = Color::PercentToRGB(value.getR());
            pixels[i++] = Color::PercentToRGB(value.getG());
            pixels[i++] = Color::PercentToRGB(value.getB());
            pixels[i++] = 255;
        }
        return std::unique_ptr<sf::Uint8>(pixels);
    }

    void SceneInteractive::setRColorToImg(const std::vector<Raytracer::Color> &vectorRes)
    {
        for (size_t x = 0, y = 0; const auto &value : vectorRes) {
            if (value.getR() != 0)
                m_img.setPixel(0, 0, sf::Color(0));
            if (x >= m_dimension.getWidth()) {
                x = 0;
                y++;
            }
            m_img.setPixel(x, y, RColorToSFColor(value));
            x++;
        }
    }

} // namespace Raytracer
