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
                    m_selectedObject = -1;
                m_objectSelection = ObjectSelection::PRIMITIVE;
                if (ImGui::BeginChild("primitive selection", ImVec2(m_leftPaneWidth,
                m_imageHeight / 2 - 20), ImGuiChildFlags_Border)) {
                    guiAddPrimitive();
                    int i = 0;
                    for (auto &prim : m_scene->getPrimitives()) {
                        std::string name = std::to_string(i) + " id" +
                            std::to_string(prim->getID()) + " " + prim->getTypeString();

                        if (ImGui::Selectable(name.c_str(), m_selectedObject == i))
                            m_selectedObject = i;
                        ImGui::SameLine();
                        if (prim->getMaterial()->getType() == MaterialType::SOLID)
                            guiColoredSquare(static_cast<MaterialSolid *>(prim->getMaterial())->getColor());
                        i++;
                    }
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Lights")) {
                if (m_objectSelection != ObjectSelection::LIGHT)
                    m_selectedObject = -1;
                m_objectSelection = ObjectSelection::LIGHT;
                guiAddLight();
                SceneLightning &lightSystem = m_scene->getLightSystem();
                if (ImGui::BeginChild("light selection", ImVec2(m_leftPaneWidth,
                m_imageHeight / 2 - 20), ImGuiChildFlags_Border)) {
                    int i = 0;
                    // Create a vector with all the lights
                    std::vector<ILight *> lightVector;
                    for (auto &aLight : lightSystem.getAmbientLights())
                        lightVector.push_back(aLight.get());
                    for (auto &dLight : lightSystem.getDirectionalLights())
                        lightVector.push_back(dLight.get());
                    for (auto &pLight : lightSystem.getLights())
                        lightVector.push_back(pLight.get());

                    for (auto &light : lightVector) {
                        std::string name = std::to_string(i) + " " + light->getTypeString();

                        if (ImGui::Selectable(name.c_str(), m_selectedObject == i))
                            m_selectedObject = i;
                        ImGui::SameLine();
                        guiColoredSquare(light->getColor());
                        i++;
                    }
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Cameras")) {
                if (m_objectSelection != ObjectSelection::CAMERA)
                    m_selectedObject = -1;
                m_objectSelection = ObjectSelection::CAMERA;
                if (ImGui::BeginChild("camera selection", ImVec2(m_leftPaneWidth,
                m_imageHeight / 2 - 20), ImGuiChildFlags_Border)) {
                    if (ImGui::Button("Add Camera")) {
                        m_scene->addCamera(std::make_unique<Camera>());
                    }
                    int i = 0;
                    for (auto &camera : m_scene->getCameras()) {
                        (void)camera;
                        std::string name = std::to_string(i) + " Camera";

                        if (ImGui::Selectable(name.c_str(), m_selectedObject == i)) {
                            m_scene->setCameraIndex(i);
                            Camera &currentCamera = m_scene->getCurrentCamera();
                            m_interacCam.setCamera(&currentCamera);
                            updateDimension(currentCamera.getDimension().getWidth(),
                                currentCamera.getDimension().getHeight());
                            m_needRendering = true;
                            m_selectedObject = i;
                        }
                        i++;
                    }
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
        #endif
    }
} // namespace Raytracer
