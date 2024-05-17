/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiEditCameras
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiEditCameras(void)
    {
        if (ImGui::Button("Delete Camera")) {
            removeSelectedObject();
            return;
        }
    }
} // namespace Raytracer
