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
        sf::Event event;
        if (m_isWriting)
            resetActions();
        while (m_window.pollEvent(event)) {
            #ifdef BONUS
                ImGui::SFML::ProcessEvent(m_window, event);
            #endif

            if (event.type == sf::Event::Closed) {
                Parsing::saveScene(*m_scene, TEMP_CFG_FILE);
                return m_window.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                #ifndef BONUS
                    updateDimension(event.size.width, event.size.height);
                #else
                    setupImageSize();
                #endif
                m_window.setView(sf::View(visibleArea));
                m_needRendering = true;
            }
            if (!m_isWriting && event.type == sf::Event::KeyReleased)
                applyKeyReleasedActions(event.key.code);
            if (!m_isWriting && event.type == sf::Event::KeyPressed)
                applyKeyPressedActions(event.key.code);
            if (!m_isWriting && m_interacCam.handleInput(event, m_actions)) {
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    m_useSimpleMouse = false;
                }
                if (event.mouseButton.button == sf::Mouse::Middle) {
                    releaseSelectedPrimitive();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    minecraftPlaceBlock();
                    if (!m_useMouse) {
                        m_useSimpleMouse = true;
                        m_lastMousePos = sf::Mouse::getPosition();
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    minecraftDestroyBlock();
                }
                if (event.mouseButton.button == sf::Mouse::Middle) {
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
