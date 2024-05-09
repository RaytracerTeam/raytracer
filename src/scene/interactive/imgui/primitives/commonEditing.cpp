/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** commonEditing
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiColoredSquare(const Color &color)
    {
        (void)color;
        #ifdef BONUS
        ImGui::ColorButton(" ", ImVec4(color.getR(),
            color.getG(), color.getB(), 1.0f),
            ImGuiColorEditFlags_InputRGB);
        #endif
    }
} // namespace Raytracer
