/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteraction.cpp
*/

#include "Scene/Interactive/CameraInteractive.hpp"
#include "Scene/Interactive/SceneInteractive.hpp"

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

// Temp
#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Materials/MaterialSolid.hpp"


namespace Raytracer {
    SceneInteractive::SceneInteractive(Dimension &dimension, const std::string &title)
        : m_dimension(dimension)
        , m_window(sf::VideoMode(dimension.getWidth(), dimension.getHeight()), title)
    {
        m_texture.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_img.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_window.setFramerateLimit(24);
        setupActions();
        #ifdef BONUS
            ImGui::SFML::Init(m_window);
        #endif
    }
    SceneInteractive::~SceneInteractive()
    {
        #ifdef BONUS
            ImGui::SFML::Shutdown();
        #endif
    }

    void SceneInteractive::updateDimension(unsigned int width, unsigned int height)
    {
        m_dimension.setWidth(width);
        m_dimension.setHeight(height);
        m_texture.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_img.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_scene->getCurrentCamera().setDimension(m_dimension);
    }

    void SceneInteractive::handleEvents(void)
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            #ifdef BONUS
                ImGui::SFML::ProcessEvent(event);
            #endif

            if (event.type == sf::Event::Closed)
                return m_window.close();
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);

                updateDimension(event.size.width, event.size.height);
                m_window.setView(sf::View(visibleArea));
                m_needRendering = true;
            }
            if (m_interacCam.handleInput(event, m_window, m_actions)) {
                m_newEvent = true;
            }
            if (m_interacCam.isActiveMouse())
                m_interacCam.handleMouse(event, m_window);
        }
        applyActions();
    }

    void SceneInteractive::handleImGui(float *spherePos, float *sphereColor)
    {
        #ifdef BONUS
            ImGui::SFML::Update(m_window, m_deltaClock.restart());

            ImGui::Begin("What a nice tool, Thank you Mister Pommier");
            ImGui::Button("Look at this pretty button");
            if (ImGui::SliderFloat3("Position", spherePos, -10, 10) ||
                ImGui::ColorPicker3("Color", sphereColor)) {
                m_needRendering = true;
            }
            ImGui::End();
        #endif
    }

    void SceneInteractive::setScene(Scene *scene)
    {
        m_scene = scene;
        m_interacCam.setCamera(&scene->getCurrentCamera());
    }

    void SceneInteractive::loop(void)
    {
        float spherePos[3] = {0, 0, 0};
        float sphereColor[3] = {1, 0, 0};
        while (m_window.isOpen()) {
            handleEvents();
            handleImGui(spherePos, sphereColor);

            Sphere *sphere = dynamic_cast<Sphere *>(m_scene->getPrimitives()[0].get());
            if (sphere) {
                std::cout << "Sphere found " << sphere << std::endl;
                sphere->setOrigin(Math::Vector3D(spherePos));
                sphere->setMaterial(std::make_unique<MaterialSolid>(Color(sphereColor)));
            }

            if (m_newEvent) {
                m_newEvent = false;
                m_scene->updatePrimitives(); // todo : unoptimized
            }
            if (m_needRendering) {
                m_needRendering = false;
                m_lastRender = RColorToPixelBuffer(m_scene->render());
            }
            m_img.create(m_dimension.getWidth(), m_dimension.getHeightD(), m_lastRender.get());

            m_texture.update(m_img);
            m_window.clear();
            m_window.draw(sf::Sprite(m_texture));
            #ifdef BONUS
                ImGui::SFML::Render(m_window);
            #endif
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
