/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.hpp
*/

#pragma once

#include <string>
#include "Scene/Scene.hpp"

namespace Raytracer {
    namespace Parsing {
        void parse(Scene &scene, const Dimension &dim, const std::string &pathname);
    } // namespace Parsing
} // namespace Raytracing
