/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** SceneInteractive.hpp
*/

#pragma once

#include "Scene/Scene.hpp"
#include "Scene/Interactive/CameraInteractive.hpp"

#include "Scene/Primitives/AllPrimitives.hpp"

#ifdef BONUS
    #include "imgui.h"
    #include "imgui-SFML.h"
#endif

#include <filesystem>

#include <SFML/Graphics.hpp>

namespace Raytracer {
    #define DEFAULT_MOVEMENT_SPEED 0.3f
    #define DEFAULT_ROTATION_SPEED 3
    #define SCREEN_RATIO 16.0f / 9.0f
    #define DEFAULT_CAMERA_RESOLUTION 240
    #define FILE_BUF_SIZE 100

    // ImGui default slider values
    #define DEFAULT_POS_MIN -60.0f
    #define DEFAULT_POS_MAX 60.0f
    #define DEFAULT_RADIUS_MIN 0.02f
    #define DEFAULT_RADIUS_MAX 40.0f
    #define DEFAULT_HEIGHT_MIN 0.0f
    #define DEFAULT_HEIGHT_MAX 40.0f
    #define DEFAULT_INTENSITY_MIN 0.0f
    #define DEFAULT_INTENSITY_MAX 100.0f

    #define MOUSE_CENTER sf::Vector2i(700, 500)

    enum class ObjectSelection {
        PRIMITIVE,
        LIGHT,
        CAMERA
    };

    class SceneInteractive {
    public:
        SceneInteractive(Dimension &dimension, const std::string &title,
            const std::vector<std::string_view> &inputFiles);
        ~SceneInteractive();

        void loop(void);

        void setScene(const std::string &filename);
        void setScenes(const std::vector<std::string_view> &inputFiles);

        static inline sf::Color RColorToSFColor(const Color &color)
        {
            return sf::Color(
                Color::PercentToRGB(color.getR()),
                Color::PercentToRGB(color.getG()),
                Color::PercentToRGB(color.getB()));
        }

    private:

        // Keys actions
        void setupActions(void);
        void resetActions(void);
        void parseConfigFile(const std::string &filename);
        void applyActions(void);
        void applyKeyReleasedActions(sf::Keyboard::Key key);
        void applyKeyReleasedAction(SceneReleaseActions action);
        void handleMouse(void);

        void updateDimension(unsigned int width, unsigned int height);
        void setupCamera(void);

        std::unique_ptr<sf::Uint8[]> RColorToPixelBuffer(const std::vector<Raytracer::Color> &vectorRes);
        void setRColorToImg(const std::vector<Raytracer::Color> &vectorRes);
        void handleEvents(void);
        float getFramerate(void);

        // -- ImGui --
        void setupImageSize(void);
        void handleImGui(void);
        void guiMenuBar(void);
        void guiTopBar(void);
        void guiDebugInfos(void);
        void guiObjectSelection(void);
        void removeSelectedObject(void);
        void customEditPrimitives(std::unique_ptr<IPrimitive> &primitive);
        void guiEditLights(void);
        void guiEditPrimitives(void);
        void guiEditCameras(void);
        void guiAddPrimitive(void);
        void editSphere(Sphere *sphere);
        void editPlane(Plane *plane);
        void editCylinder(Cylinder *cylinder);
        void editCone(Cone *cone);
        void editTorus(Torus *torus);
        void editTanglecube(Tanglecube *tanglecube);
        void editTriangle(Triangle *triangle);
        void addSelectableSkybox(const std::filesystem::directory_entry &entry);
        void addSelectableScene(const std::filesystem::directory_entry &entry);

        /////////////////////////////////

        std::unique_ptr<Scene> m_scene;
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
        size_t m_renderResolution;
        char m_fileBuf[FILE_BUF_SIZE] = "scenes/";
        char m_skyboxPathBuf[FILE_BUF_SIZE] = DEFAULT_SKYBOX;
        char m_cfgSceneBuf[FILE_BUF_SIZE] = "scenes/";
        bool m_isWriting = false;
        bool m_showDebug = false;
        bool m_addToCurrentScene = false;
        int m_selectedObject = -1;
        ObjectSelection m_objectSelection = ObjectSelection::PRIMITIVE;
        size_t m_imageHeight;
        size_t m_imageWidth;
        size_t m_leftPaneWidth;

        // Storing the result of the render
        std::unique_ptr<sf::Uint8 []> m_lastRender;

        // Actions
        std::vector<std::pair<sf::Keyboard::Key, bool>> m_actions;
        std::vector<sf::Keyboard::Key> m_releaseActions;
        bool m_newEvent = true;
        bool m_needRendering = true;
        float m_movementSpeed = DEFAULT_MOVEMENT_SPEED;
        float m_defaultMovementSpeed = DEFAULT_MOVEMENT_SPEED;
        float m_rotationSpeed = DEFAULT_ROTATION_SPEED;
        bool m_useSimpleMouse = false;
        sf::Vector2i m_lastMousePos;
        bool m_useMouse = false;
        sf::Vector2i m_mouseCenterCorrection = {0, 0};
        sf::Vector2i m_mousePosBeforeUse = {0, 0};
        int m_mouseCentered = 0;
    };
} // namespace Raytracer
