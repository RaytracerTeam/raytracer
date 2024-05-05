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
        #ifdef BONUS
        if (ImGui::Button("Delete Camera")) {
            removeSelectedObject();
            return;
        }
        #endif
    }
} // namespace Raytracer
