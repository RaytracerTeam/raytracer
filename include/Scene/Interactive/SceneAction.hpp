/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** SceneAction
*/

#pragma once

namespace Raytracer
{
    enum SceneAction {
        MOVE_FORWARD,
        MOVE_BACKWARD,
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        ROTATE_UP,
        ROTATE_DOWN,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        SPRINT,
        EXIT,
        QUICK_SAVE,
        SAVE_AND_EXIT,
        SHOW_FPS,
        RESET
    };
} // namespace Raytracer
