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
                "scenes/custom_scene.cfg", m_fileBuf, FILE_BUF_SIZE,
                ImGuiInputTextFlags_EnterReturnsTrue)) {
                    if (std::filesystem::exists(m_fileBuf)) {
                        setScene(m_fileBuf);
                        m_needRendering = true;
                    }
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine(0, 20),
                ImGui::Checkbox("Add to current scene", &m_addToCurrentScene);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Skybox path")) {
                m_isWriting = true;
                if (ImGui::InputTextWithHint(" Path to sphere image (press ENTER to save)",
                "assets/skyboxes/sky.jpg", m_skyboxPathBuf, FILE_BUF_SIZE,
                ImGuiInputTextFlags_EnterReturnsTrue)) {
                    if (std::filesystem::exists(m_skyboxPathBuf))
                        m_scene->setSkyboxPath(m_skyboxPathBuf);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMenuBar();
        #endif
    }
} // namespace Raytracer
