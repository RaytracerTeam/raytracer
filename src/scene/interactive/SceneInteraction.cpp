/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteraction.cpp
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Parsing/Parsing.hpp"

#include <cstring>
#include <thread>

//todo : remove this when camera implementation done
#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"

namespace Raytracer {
    SceneInteractive::SceneInteractive(Dimension &dimension, const std::string &title,
        const std::vector<std::string_view> &inputFiles)
        : m_dimension(dimension)
    {
        m_scene = std::make_unique<Scene>();
        setScenes(inputFiles);
        setupCamera();
        m_scene->updatePrimitives();
        m_alwaysRender = m_scene->getAlwaysRender();

        #ifdef BONUS
        if (inputFiles.size() > 0)
            strcpy(m_loadFileBuf, inputFiles[0].data());
        #endif

        sf::Vector2u windowSize;
        #ifndef MACOSTONIO
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        #endif

        #ifdef BONUS
            #ifdef MACOSTONIO
                windowSize = sf::Vector2u(1440, 850);
            #else
                windowSize = sf::Vector2u(desktop.width, desktop.height);
            #endif
        #else
            Camera *camera = m_interacCam.getCamera();
            windowSize = sf::Vector2u(camera->getDimension().getWidth(),
                camera->getDimension().getHeight());
        #endif

        m_window.create(sf::VideoMode(windowSize.x, windowSize.y), title);
        #ifndef MACOSTONIO
        m_window.setPosition(sf::Vector2i(desktop.width / 2, desktop.height / 2)
            - sf::Vector2i(windowSize.x / 2, windowSize.y / 2));
        #endif

        #ifdef BONUS
            if (!ImGui::SFML::Init(m_window))
                throw std::runtime_error("Failed to initialize ImGui");
            m_leftPaneWidth = 270;
            setupImageSize();
        #endif

        m_window.setFramerateLimit(WINDOW_FPS);
        setupActions();
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
        m_renderResolution = m_dimension.getHeight();
        m_texture.create(m_dimension.getWidth(), m_dimension.getHeight());
        Camera *camera = m_interacCam.getCamera();
        if (camera)
            camera->setDimension(m_dimension);
        m_scene->setRenderNbr(m_scene->getRenderNbr() + 1);
        m_scene->resizeRender(width, height);
    }

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
            if (!m_isWriting && m_interacCam.handleInput(event, m_actions)) {
            }
            if (event.type == sf::Event::MouseButtonReleased
            && event.mouseButton.button == sf::Mouse::Right) {
                m_useSimpleMouse = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    m_useSimpleMouse = true;
                    m_lastMousePos = sf::Mouse::getPosition();
                }
                #ifdef BONUS
                // Select primitive by aiming at it with the center of the screen
                else if (event.mouseButton.button == sf::Mouse::Left && (m_useMouse || m_useSimpleMouse)) {
                    const IShape *shape = m_scene->getPrimitiveHit(sf::Vector2i(
                        m_dimension.getWidth() / 2, m_dimension.getHeight() / 2
                    ));
                    if (shape) {
                        int i = 0;
                        for (auto &prim : m_scene->getPrimitives()) {
                            if (prim->getID() == shape->getID()) {
                                m_selectedObject = i;
                                m_selectPrimitiveTab = true;
                                break;
                            }
                            i++;
                        }
                    }
                }
                #endif
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
            m_scene->reset();
        Parsing::parse(m_scene, filename);
        // parseInteractive(filename);
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
    }

    void SceneInteractive::loop(void)
    {
        while (m_window.isOpen()) {
            handleEvents();
            #ifdef BONUS
            handleImGui();
            #endif
            #ifdef BONUSCAMERA
            m_scene->updateRealCamera();
            #endif

            if (m_updateBVH) {
                m_scene->setRenderNbr(m_scene->getRenderNbr() + 1);
                m_updateBVH = false;
                m_waitThread = true;
            }
            if (m_waitThread && m_scene->getNbThreadsAlive() == 0) {
                m_waitThread = false;
                m_scene->killObjects();
                m_scene->updatePrimitives();
            }
            if ((m_needRendering || m_alwaysRender) && !m_waitThread) {
                float timeSinceLastFrame = m_renderClock.getElapsedTime().asSeconds();
                bool renderDone = m_scene->getRenderY() >= m_dimension.getHeight();
                if ((renderDone && timeSinceLastFrame > 1 / m_maxFramerate)
                || timeSinceLastFrame > 1 / m_minFramerate) {
                    m_framerate = 1 / timeSinceLastFrame;
                    m_needRendering = false;
                    m_renderClock.restart();
                    if (m_scene->getNbThreads() < 2)
                        m_scene->renderWhitoutThread();
                    else
                        std::thread(&Scene::render, m_scene.get()).detach();
                }
            }

            m_texture.update(m_scene->getRender());

            m_window.clear();
            #ifndef BONUS
                m_window.draw(sf::Sprite(m_texture));
            #endif
            #ifdef BONUS
                ImGui::SFML::Render(m_window);
            #endif
            m_window.display();
        }
        m_scene->setRenderNbr(m_scene->getRenderNbr() + 1);
    }
} // namespace Raytracer
