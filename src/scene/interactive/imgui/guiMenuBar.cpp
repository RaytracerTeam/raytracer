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
        #ifdef BONUS
        std::string path = entry.path().string();
        if (path.ends_with(".jpg") &&
        ImGui::Selectable(path.c_str())) {
            m_scene->setSkyboxPath(entry.path().string());
            m_needRendering = true;
            strcpy(m_skyboxPathBuf, path.c_str());
            ImGui::CloseCurrentPopup();
        }
        #endif
    }

    void SceneInteractive::addSelectableScene(const std::filesystem::directory_entry &entry)
    {
        #ifdef BONUS
        std::string path = entry.path().string();
        if (path.ends_with(".cfg") &&
        ImGui::Selectable(path.c_str())) {
            setScene(entry.path().string());
            setupCamera();
            m_needRendering = true;
            strcpy(m_cfgSceneBuf, path.c_str());
            ImGui::CloseCurrentPopup();
        }
        #endif
    }

    void SceneInteractive::guiMenuBar(void)
    {
        #ifdef BONUS
        m_isWriting = false;
        if (ImGui::BeginMenuBar()) {
            // Save scene to .cfg
            if (ImGui::BeginMenu("Save as ...")) {
                m_isWriting = true;
                std::string hint("custom_scene.cfg");
                if (ImGui::InputTextWithHint(" File name (press ENTER to save)",
                hint.c_str(), m_fileBuf, FILE_BUF_SIZE,
                ImGuiInputTextFlags_EnterReturnsTrue)) {
                    Parsing::saveScene(*m_scene, m_fileBuf);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Load scene")) {
                m_isWriting = true;
                if (ImGui::InputTextWithHint(" File name (press ENTER to load)",
                "scenes/custom_scene.cfg", m_cfgSceneBuf, FILE_BUF_SIZE,
                ImGuiInputTextFlags_EnterReturnsTrue)) {
                    if (std::filesystem::exists(m_cfgSceneBuf)) {
                        setScene(m_cfgSceneBuf);
                        setupCamera();
                        m_needRendering = true;
                    }
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine(0, 20),
                ImGui::Checkbox("Add to current scene", &m_addToCurrentScene);
                if (ImGui::BeginCombo("Scene Path", m_cfgSceneBuf)) {
                    for (const auto &entry : std::filesystem::directory_iterator("scenes/"))
                        addSelectableScene(entry);
                    if (std::filesystem::exists("scenes/local"))
                        for (const auto &entry : std::filesystem::directory_iterator("scenes/local"))
                            addSelectableScene(entry);

                    ImGui::EndCombo();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Skybox path")) {
                m_isWriting = true;
                bool skyboxHasTexture = m_scene->getSkybox().hasTexture();
                if (ImGui::Checkbox("Has texture", &skyboxHasTexture)) {
                    m_scene->getSkybox().setHasTexture(skyboxHasTexture);
                    m_needRendering = true;
                }
                if (skyboxHasTexture) {

                    if (ImGui::InputTextWithHint(" Path to sphere image (press ENTER to save)",
                    "assets/skyboxes/sky.jpg", m_skyboxPathBuf, FILE_BUF_SIZE,
                    ImGuiInputTextFlags_EnterReturnsTrue)) {
                        if (std::filesystem::exists(m_skyboxPathBuf))
                            m_scene->setSkyboxPath(m_skyboxPathBuf);
                        ImGui::CloseCurrentPopup();
                    }
                    if (ImGui::BeginCombo("Skybox Path", m_skyboxPathBuf)) {
                        for (const auto &entry : std::filesystem::directory_iterator("assets/skyboxes"))
                            addSelectableSkybox(entry);
                        if (std::filesystem::exists("assets/skyboxes/local"))
                            for (const auto &entry : std::filesystem::directory_iterator("assets/skyboxes/local"))
                                addSelectableSkybox(entry);

                        ImGui::EndCombo();
                    }
                } else {
                    Skybox &skybox = m_scene->getSkybox();
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
        #endif
    }
} // namespace Raytracer
