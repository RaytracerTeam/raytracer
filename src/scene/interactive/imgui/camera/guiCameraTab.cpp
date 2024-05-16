/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiObjectSelection
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiCameraTab(void)
    {
        if (ImGui::BeginTabItem("Camera")) {
            if (m_objectSelection != ObjectSelection::CAMERA)
                m_selectedObject = -1;
            m_objectSelection = ObjectSelection::CAMERA;
            if (ImGui::Button("Add Camera")) {
                m_scene->addCamera(std::make_unique<Camera>());
            }
            if (ImGui::BeginChild("camera selection", ImVec2(m_leftPaneWidth,
            m_imageHeight / 2 - 20), ImGuiChildFlags_Border)) {
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
} // namespace Raytracer
