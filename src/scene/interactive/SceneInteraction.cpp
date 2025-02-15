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
        m_defaultMovementSpeed = m_scene->getCameraSpeed();
        m_rotationSpeed = m_scene->getCameraSensitivity();
        #ifdef BONUS
        m_skyboxPathBuf[0] = '\0';
        if (inputFiles.size() > 0)
            strcpy(m_loadFileBuf, inputFiles[0].data());
        #endif
        #ifdef BONUSCAMERA
        m_scene->initRealCamera();
        m_scene->updateRealCamera();
        #endif

        sf::Vector2u windowSize;
        #ifndef MACOSTONIO
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        #endif

        #ifdef BONUS
            #ifdef MACOSTONIO
                windowSize = sf::Vector2u(1440, 850);
            #else
                windowSize = sf::Vector2u(desktop.size.x, desktop.size.y);
            #endif
        #else
            Camera *camera = m_interacCam.getCamera();
            windowSize = sf::Vector2u(camera->getDimension().getWidth(),
                camera->getDimension().getHeight());
        #endif

        m_window.create(sf::VideoMode(sf::Vector2u(windowSize.x, windowSize.y)), title);
        #ifndef MACOSTONIO
        m_window.setPosition(sf::Vector2i(desktop.size.x / 2, desktop.size.y / 2)
            - sf::Vector2i(windowSize.x / 2, windowSize.y / 2));
        #endif

        #ifdef BONUS
            if (!ImGui::SFML::Init(m_window))
                throw std::runtime_error("Failed to initialize ImGui");
            m_leftPaneWidth = 270;
            setupImageSize();
            m_leftPaneChildHeight = m_imageHeight / 2 - 40;
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
        m_texture.resize(sf::Vector2u(m_dimension.getWidth(), m_dimension.getHeight()));
        Camera *camera = m_interacCam.getCamera();
        if (camera)
            camera->setDimension(m_dimension);
        m_scene->setRenderNbr(m_scene->getRenderNbr() + 1);
        m_scene->resizeRender(width, height);
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
