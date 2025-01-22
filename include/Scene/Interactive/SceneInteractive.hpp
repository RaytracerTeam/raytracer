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
    #define DEFAULT_CAMERA_RESOLUTION 240
    #define FILE_BUF_SIZE 4096
    #define LEFT_PANE_PADDING 30

    // ImGui default slider values
    #define DEFAULT_POS_MIN -60.0f
    #define DEFAULT_POS_MAX 60.0f
    #define DEFAULT_RADIUS_MIN 0.02f
    #define DEFAULT_RADIUS_MAX 40.0f
    #define DEFAULT_HEIGHT_MIN 0.0f
    #define DEFAULT_HEIGHT_MAX 40.0f
    #define DEFAULT_INTENSITY_MIN 0.0f
    #define DEFAULT_INTENSITY_MAX 1.5f

    #define WINDOW_FPS 60

    #define MOUSE_CENTER sf::Vector2i(700, 500)

    #define TEMP_CFG_FILE "scenes/temp.cfg"
    #define QUICK_SAVE_CFG_FILE "scenes/quick_save.cfg"

    #define OBJ_PATH "assets/obj/"
    #define OBJ_LOCAL_PATH "assets/obj/local/"
    #define OBJ_PATHS {OBJ_PATH, OBJ_LOCAL_PATH}
    #define TEXTURE_PATH "assets/textures/local/"
    #define TEXTURE_MINECRAFT_PATH "assets/textures/minecraft"
    #define TEXTURE_OBJ_PATH "assets/textures/obj/"
    #define TEXTURE_PATHS {TEXTURE_PATH, TEXTURE_MINECRAFT_PATH, TEXTURE_OBJ_PATH}
    #define SCENE_PATH "scenes/"
    #define SCENE_LOCAL_PATH "scenes/local/"
    #define SCENE_DEMO_PATH "scenes/demo/"
    #define SCENE_DEMO_OBJ_PATH "scenes/demo/obj/"
    #define SCENE_DEMO_PRIMITIVES_PATH "scenes/demo/primitives/"
    #define SCENE_PATHS {SCENE_PATH, SCENE_DEMO_PATH, SCENE_LOCAL_PATH, SCENE_DEMO_OBJ_PATH, SCENE_DEMO_PRIMITIVES_PATH}
    #define SKYBOX_LOCAL_PATH "assets/skyboxes/local/"
    #define SKYBOX_PATH "assets/skyboxes"
    #define SKYBOX_PATHS {SKYBOX_PATH, SKYBOX_LOCAL_PATH}

    enum class ObjectSelection {
        PRIMITIVE,
        LIGHT,
        CAMERA,
        OBJ,
        INVENTORY
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
        void applyKeyPressedActions(sf::Keyboard::Key key);
        void applyKeyPressedAction(SceneReleaseActions action);
        void handleMouse(void);

        void updateDimension(unsigned int width, unsigned int height);
        void setupCamera(void);

        void setRColorToImg(const std::vector<Raytracer::Color> &vectorRes);
        void handleEvents(void);

        void selectShootedPrimitive(void);
        void releaseSelectedPrimitive(void);

        // Welcome in Minecraft
        void showCrosshair(void);
        void minecraftPlaceBlock(void);
        void minecraftDestroyBlock(void);

        Math::Vector3D getCameraFrontPos(void);
        std::unique_ptr<IMaterial> copyMaterial(IMaterial *material);

        // -- ImGui --
        #ifdef BONUS
        void setupImageSize(void);
        void handleImGui(void);
        void guiMenuBar(void);
        void guiTopBar(void);
        void guiDebugInfos(void);
        void guiObjectSelection(void);
        void guiPrimitiveTab(void);
        void guiLightTab(void);
        void guiCameraTab(void);
        void guiObjTab(void);
        void guiInventoryTab(void);

        void removeSelectedObject(void);
        void customEditPrimitives(std::unique_ptr<IPrimitive> &primitive);
        void customEditLights(ILight *light);
        bool customEditMaterial(std::unique_ptr<IMaterial> &material);
        bool changeMaterialType(std::unique_ptr<IMaterial> &material);
        bool guiEditMaterial(std::unique_ptr<IMaterial> &material);
        void guiEditLights(void);
        void guiEditPrimitives(void);
        void guiEditObjs(void);
        void guiEditCameras(void);
        void guiEditInventory(void);
        void guiAddPrimitive(void);
        void guiAddObj(void);
        void guiAddLight(void);
        void editSphere(Sphere *sphere);
        void editPlane(Plane *plane);
        void editCylinder(Cylinder *cylinder);
        void editCone(Cone *cone);
        void editTorus(Torus *torus);
        void editTanglecube(Tanglecube *tanglecube);
        void editTriangle(Triangle *triangle);
        void editCube(Cube *cube);

        void editPointLight(PointLight *light);
        void editDirectionalLight(DirectionalLight *light);

        void addSelectableSkybox(const std::filesystem::directory_entry &entry);
        void addSelectableScene(const std::filesystem::directory_entry &entry);

        void guiColoredSquare(const Color &color);
        #endif

        /////////////////////////////////

        std::unique_ptr<Scene> m_scene;
        CameraInteractive m_interacCam;

        Dimension &m_dimension;
        sf::RenderWindow m_window;
        sf::Texture m_texture;

        sf::Clock m_clock;

        sf::Clock m_renderClock;
        float m_minFramerate = 10;
        float m_maxFramerate = WINDOW_FPS;
        float m_framerate = 0;

        // ImGui
        #ifdef BONUS
        sf::Clock m_deltaClock;
        char m_saveFileBuf[FILE_BUF_SIZE] = SCENE_PATH;
        char m_skyboxPathBuf[FILE_BUF_SIZE];
        char m_loadFileBuf[FILE_BUF_SIZE] = SCENE_PATH;
        bool m_showDebug = true;
        int m_selectedObject = -1;
        ObjectSelection m_objectSelection = ObjectSelection::PRIMITIVE;
        size_t m_leftPaneWidth;
        size_t m_leftPaneChildHeight;
        bool m_fullscreen = false;
        bool m_selectPrimitiveTab = false;
        bool m_saveObjAsPrimitives = false;
        IPrimitive *m_selectedPrimitive = nullptr;
        float m_selectedPrimitiveSpecular;
        float m_selectedPrimitiveShininess;
        float m_selectedPrimitiveTransparency;
        #endif
        bool m_addToCurrentScene = false;
        bool m_isWriting = false;
        size_t m_renderResolution;
        size_t m_imageHeight;
        size_t m_imageWidth;
        bool m_alwaysRender = false;
        float m_reach = 10;

        // Storing the result of the render
        std::unique_ptr<std::uint8_t []> m_lastRender;

        // Actions
        std::vector<std::pair<sf::Keyboard::Key, bool>> m_actions;
        std::vector<sf::Keyboard::Key> m_releaseActions;
        bool m_updateBVH = true;
        bool m_waitThread = false;
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
