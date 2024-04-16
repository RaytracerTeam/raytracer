/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.h
*/

#pragma once

#include "IPrimitive.hpp"

namespace Raytracer {
    class APrimitive : public IPrimitive {
        private:
            APrimitive() = default;
            ~APrimitive() = default;
    };
} // namespace Raytracer
