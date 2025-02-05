/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** handleEvents.cpp
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Parsing/Parsing.hpp"


namespace Raytracer {
    void SceneInteractive::handleEvents(void)
    {
        #ifdef BONUS
        if (ImGui::IsAnyItemActive())
            resetActions();
        #endif

        while (const std::optional<sf::Event> event = m_window.pollEvent()) {
            #ifdef BONUS
            ImGui::SFML::ProcessEvent(m_window, *event);
            #endif

            if (event->is<sf::Event::Closed>()) {
                Parsing::saveScene(*m_scene, TEMP_CFG_FILE);
                m_window.close();
                return;
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(resized->size.x, resized->size.y));
                #ifndef BONUS
                    updateDimension(resized->size.x, resized->size.y);
                #else
                    setupImageSize();
                #endif
                m_window.setView(sf::View(visibleArea));
                m_needRendering = true;
            }

            #ifdef BONUS
            if (!ImGui::IsAnyItemActive()) {
            #endif
                if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                    applyKeyReleasedActions(keyReleased->code);
                }
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    applyKeyPressedActions(keyPressed->code);
                }
                if (m_interacCam.handleInput(*event, m_actions)) {
                    // Handle camera input
                }
            #ifdef BONUS
            }
            #endif

            if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseReleased->button == sf::Mouse::Button::Right) {
                    m_useSimpleMouse = false;
                }
                if (mouseReleased->button == sf::Mouse::Button::Middle) {
                    releaseSelectedPrimitive();
                }
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Right) {
                    minecraftPlaceBlock();
                    if (!m_useMouse) {
                        m_useSimpleMouse = true;
                        m_lastMousePos = sf::Mouse::getPosition();
                    }
                }
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    minecraftDestroyBlock();
                }
                if (mousePressed->button == sf::Mouse::Button::Middle) {
                    selectShootedPrimitive();
                }
            }
        }
        if (m_useMouse)
            showCrosshair();
        handleMouse();
        applyActions();
    }

} // namespace Raytracer
