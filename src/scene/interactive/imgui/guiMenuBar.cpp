/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiMenuBar
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void SceneInteractive::addSelectableSkybox(const std::filesystem::directory_entry &entry)
    {
        std::string path = entry.path().string();
        if (path.ends_with(".jpg") &&
        ImGui::Selectable(path.c_str())) {
            m_scene->setSkyboxPath(entry.path().string());
            m_needRendering = true;
            strcpy(m_skyboxPathBuf, path.c_str());
            ImGui::CloseCurrentPopup();
        }
    }

    void SceneInteractive::addSelectableScene(const std::filesystem::directory_entry &entry)
    {
        std::string path = entry.path().string();
        if (path.ends_with(".cfg") &&
        ImGui::Selectable(path.c_str())) {
            setScene(path);
            setupCamera();
            m_needRendering = true;
            m_updateBVH = true;
            strcpy(m_loadFileBuf, path.c_str());
            ImGui::CloseCurrentPopup();
        }
    }

    void SceneInteractive::guiMenuBar(void)
    {
        m_isWriting = false;
        if (ImGui::BeginMenuBar()) {
            // Save scene to .cfg
            if (ImGui::BeginMenu("Save as ...")) {
                m_isWriting = true;
                std::string hint("custom_scene.cfg");
                if (ImGui::InputTextWithHint(" File name (press ENTER to save)",
                hint.c_str(), m_saveFileBuf, FILE_BUF_SIZE,
                ImGuiInputTextFlags_EnterReturnsTrue)) {
                    Parsing::saveScene(*m_scene, m_saveFileBuf);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine(0, 20);
                ImGui::Checkbox("Save OBJ as Primitives (WIP)", &m_saveObjAsPrimitives);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Load scene")) {
                m_isWriting = true;
                if (ImGui::InputTextWithHint(" File name (press ENTER to load)",
                "scenes/custom_scene.cfg", m_loadFileBuf, FILE_BUF_SIZE,
                ImGuiInputTextFlags_EnterReturnsTrue)) {
                    if (std::filesystem::exists(m_loadFileBuf)) {
                        setScene(m_loadFileBuf);
                        setupCamera();
                        m_needRendering = true;
                        m_updateBVH = true;
                    }
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine(0, 20),
                ImGui::Checkbox("Add to current scene", &m_addToCurrentScene);
                if (ImGui::BeginCombo("Scene Path", m_loadFileBuf)) {
                    for (const auto &path : SCENE_PATHS) {
                        if (!std::filesystem::exists(path))
                            continue;
                        for (const auto &entry : std::filesystem::directory_iterator(path)) {
                            if (entry.path().filename().extension() != ".cfg")
                                continue;
                            addSelectableScene(entry);
                        }
                    }

                    ImGui::EndCombo();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Skybox path")) {
                m_isWriting = true;
                Skybox &skybox = m_scene->getSkybox();
                bool skyboxHasTexture = skybox.hasTexture();
                if (ImGui::Checkbox("Has texture", &skyboxHasTexture)) {
                    skybox.setHasTexture(skyboxHasTexture);
                    m_needRendering = true;
                }
                if (skyboxHasTexture) {

                    if (ImGui::InputTextWithHint(" Path to sphere image (press ENTER to save)",
                    "assets/skyboxes/sky.jpg", m_skyboxPathBuf, FILE_BUF_SIZE,
                    ImGuiInputTextFlags_EnterReturnsTrue)) {
                        if (std::filesystem::exists(m_skyboxPathBuf))
                            m_scene->setSkyboxPath(m_skyboxPathBuf);
                        m_needRendering = true;
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::BeginCombo("Skybox Path", m_skyboxPathBuf)) {
                        for (const auto &path : SKYBOX_PATHS) {
                            if (!std::filesystem::exists(path))
                                continue;
                            for (const auto &entry : std::filesystem::directory_iterator(path))
                                addSelectableSkybox(entry);
                        }
                        #ifdef BONUSCAMERA
                        if (ImGui::Selectable("Use camera")) {
                            m_scene->getSkybox().getTexture()->setImage(m_scene->getRealCamera().getImage());
                            m_needRendering = true;
                        }
                        #endif
                        ImGui::EndCombo();
                    }
                    bool useSphere = skybox.getSkyboxUVTypee() == SkyboxUVType::SPHERE;
                    if (ImGui::Checkbox("Use UV Sphere", &useSphere)) {
                       skybox.setSkyboxUVTypee(useSphere ? SkyboxUVType::SPHERE : SkyboxUVType::BOX);
                        m_needRendering = true;
                    }
                } else {
                    float *color = skybox.getAmbientColor();
                    if (ImGui::ColorEdit3("Skybox Color", color)) {
                        skybox.setSolidColor(color);
                        m_needRendering = true;
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMenuBar();
    }
} // namespace Raytracer
