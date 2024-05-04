/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjectSelection
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Lights/PointLight.hpp"

namespace Raytracer
{
    void SceneInteractive::guiObjectSelection(void) {
        #ifdef BONUS
        if (ImGui::BeginTabBar("Object Selection",
        ImGuiTabBarFlags_NoCloseWithMiddleMouseButton
        | ImGuiTabBarFlags_Reorderable)) {
            if (ImGui::BeginTabItem("Primitives")) {
                if (m_objectSelection != ObjectSelection::PRIMITIVE)
                    m_selectedObject = 0;
                m_objectSelection = ObjectSelection::PRIMITIVE;
                ImGui::BeginChild("primitive selection", ImVec2(m_leftPaneWidth,
                    m_imageHeight / 2 - 20), ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Primitive", m_selectedObject == 0))
                {
                    // m_scene->addPrimitive(std::make_unique<Sphere>(
                    //     Math::Vector3D(0, 0, 0), 1,
                    //     std::make_unique<MaterialSolid>(
                    //         Color((unsigned int)255, 255, 255)),
                    //     1.0));
                    m_selectedObject = 0;
                }
                int i = 0;
                for (auto &prim : m_scene->getPrimitives())
                {
                    std::string name = std::to_string(i) + " id" +
                        std::to_string(prim->getID()) + " " + prim->getTypeString();

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i + 1))
                        m_selectedObject = i + 1;
                    i++;
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Lights")) {
                if (m_objectSelection != ObjectSelection::LIGHT)
                    m_selectedObject = 0;
                m_objectSelection = ObjectSelection::LIGHT;
                ImGui::BeginChild("light selection", ImVec2(m_leftPaneWidth,
                    m_imageHeight / 2 - 20), ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Light", m_selectedObject == 0))
                {
                    m_scene->addLight(std::make_unique<PointLight>(
                        Math::Vector3D(0, 0, 0), 1,
                        Color((unsigned int)255, 255, 255),
                        1.0));
                    m_selectedObject = 0;
                }
                int i = 0;
                for (auto &light : m_scene->getLights())
                {
                    std::string name = std::to_string(i) + " id" +
                        std::to_string(light->getID()) + " PointLight";

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i + 1))
                        m_selectedObject = i + 1;
                    i++;
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Cameras")) {
                if (m_objectSelection != ObjectSelection::CAMERA)
                    m_selectedObject = 0;
                m_objectSelection = ObjectSelection::CAMERA;
                ImGui::BeginChild("camera selection", ImVec2(m_leftPaneWidth,
                    m_imageHeight / 2 - 20), ImGuiChildFlags_Border);
                if (ImGui::Selectable("Add Camera", m_selectedObject == 0))
                {
                    m_scene->addCamera(std::make_unique<Camera>());
                    m_selectedObject = 0;
                }
                int i = 0;
                for (auto &camera : m_scene->getCameras())
                {
                    std::string name = std::to_string(i) + " Camera";

                    if (ImGui::Selectable(name.c_str(), m_selectedObject == i + 1)) {
                        m_scene->setCameraIndex(i);
                        Camera &currentCamera = m_scene->getCurrentCamera();
                        m_interacCam.setCamera(&currentCamera);
                        updateDimension(currentCamera.getDimension().getWidth(),
                            currentCamera.getDimension().getHeight());
                        m_needRendering = true;
                        m_selectedObject = i + 1;
                    }
                    i++;
                }
                ImGui::EndChild();

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        #endif
    }
} // namespace Raytracer
