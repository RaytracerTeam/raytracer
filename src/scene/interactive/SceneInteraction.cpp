/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteraction.cpp
*/

#include "Scene/Interactive/CameraInteractive.hpp"
#include "Scene/Interactive/SceneInteractive.hpp"

#include "Parsing/Parsing.hpp"
#include <cstring>

namespace Raytracer {
    SceneInteractive::SceneInteractive(Dimension &dimension, const std::string &title,
        const std::vector<std::string_view> &inputFiles)
        : m_dimension(dimension)
        , m_window(sf::VideoMode(dimension.getWidth(), dimension.getHeight()), title)
        , m_previousTime(m_clock.getElapsedTime())
    {
        m_scene = std::make_unique<Scene>();
        setScenes(inputFiles);
        setupCamera();

        if (inputFiles.size() > 0)
            strcpy(m_cfgSceneBuf, inputFiles[0].data());

        #ifdef BONUS
            #ifdef MACOSTONIO
                m_window.setSize(sf::Vector2u(1440, 850));
            #else
                m_window.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width,
                    sf::VideoMode::getDesktopMode().height));
            #endif
            m_window.setPosition(sf::Vector2i(0, 0));
            if (!ImGui::SFML::Init(m_window))
                throw std::runtime_error("Failed to initialize ImGui");
            m_leftPaneWidth = 220;
            setupImageSize();
        #endif
        m_window.setFramerateLimit(60);
        setupActions();
    }
    SceneInteractive::~SceneInteractive()
    {
        #ifdef BONUS
            ImGui::SFML::Shutdown();
        #endif
    }

    void SceneInteractive::setupImageSize(void)
    {
        #ifdef BONUS
        m_imageWidth = ImGui::GetIO().DisplaySize.x - m_leftPaneWidth - 50;
        m_imageHeight = m_imageWidth / (SCREEN_RATIO);
        #endif
    }

    void SceneInteractive::updateDimension(unsigned int width, unsigned int height)
    {
        m_dimension.setWidth(width);
        m_dimension.setHeight(height);
        m_renderResolution = m_dimension.getHeight();
        m_texture.create(m_dimension.getWidth(), m_dimension.getHeight());
        m_img.create(m_dimension.getWidth(), m_dimension.getHeight());
        Camera *camera = m_interacCam.getCamera();
        if (camera)
            camera->setDimension(m_dimension);
    }

    void SceneInteractive::handleEvents(void)
    {
        sf::Event event;

        if (m_isWriting)
            resetActions();
        while (m_window.pollEvent(event)) {
            #ifdef BONUS
                ImGui::SFML::ProcessEvent(event);
            #endif

            if (event.type == sf::Event::Closed)
                return m_window.close();
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
            if (!m_isWriting && m_interacCam.handleInput(event, m_window, m_actions)) {
                m_newEvent = true;
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                if (event.type == sf::Event::MouseButtonReleased) {
                    m_useSimpleMouse = false;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    m_useSimpleMouse = true;
                    m_lastMousePos = sf::Mouse::getPosition();
                }
            }
        }
        handleMouse();
        applyActions();
    }

    void SceneInteractive::setScenes(const std::vector<std::string_view> &inputFiles)
    {
        for (const auto &file : inputFiles) {
            setScene(std::string(file));
            m_addToCurrentScene = true;
        }
        m_addToCurrentScene = false;
    }

    void SceneInteractive::setScene(const std::string &filename)
    {
        if (!m_addToCurrentScene)
            m_scene = std::make_unique<Scene>();
        Parsing::parse(m_scene, {filename});
        int i = 0;
        for (const auto &primitive : m_scene->getPrimitives()) {
            primitive->setID(++i);
        }
        i = 0;
        for (const auto &light : m_scene->getLights()) {
            light->setID(++i);
        }
    }

    void SceneInteractive::setupCamera(void)
    {
        m_scene->setCameraIndex(0);
        if (m_scene->getCameraCount() == 0)
            m_scene->addCamera(std::make_unique<Camera>());
        Camera &currentCamera = m_scene->getCurrentCamera();
        m_interacCam.setCamera(&currentCamera);
        updateDimension(currentCamera.getDimension().getWidth(),
            currentCamera.getDimension().getHeight());
        // updateDimension(DEFAULT_CAMERA_RESOLUTION * SCREEN_RATIO, DEFAULT_CAMERA_RESOLUTION);
    }

    void SceneInteractive::loop(void)
    {
        while (m_window.isOpen()) {
            handleEvents();
            handleImGui();

            if (m_newEvent) {
                m_newEvent = false;
                // todo : make this behavior diffretn : when an object transforms
                // m_scene->updatePrimitives();
            }
            if (m_needRendering || m_alwaysRender) {
                m_needRendering = false;
                m_lastRender = RColorToPixelBuffer(m_scene->render());
                m_img.create(m_dimension.getWidth(), m_dimension.getHeight(), m_lastRender.get());
                m_texture.update(m_img);
            }

            m_window.clear();
            #ifndef BONUS
                m_window.draw(sf::Sprite(m_texture));
            #endif
            #ifdef BONUS
                ImGui::SFML::Render(m_window);
            #endif
            m_window.display();
        }
    }

    float SceneInteractive::getFramerate(void)
    {
        m_currentTime = m_clock.getElapsedTime();
        float frameTime = m_currentTime.asSeconds() - m_previousTime.asSeconds();
        m_frameTimes.push_back(frameTime);
        if (m_frameTimes.size() > 200)
            m_frameTimes.erase(m_frameTimes.begin());
        auto fps = 1.0f / frameTime;
        m_previousTime = m_currentTime;
        return fps;
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
