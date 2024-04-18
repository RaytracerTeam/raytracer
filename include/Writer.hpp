/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Writer.hpp
*/

#pragma once

#include <stddef.h>
#include <vector>
#include <string>

#include "Color.hpp"
#include "Pixels.hpp"

namespace Raytracer {
    class WriteFile {
    public:
        enum WriteType {
            PPM,
            JPG,
            PNG
        };
        static void writeImage(WriteType type, std::vector<Color> buffer, const Dimension &dimension);
    };
} // namespace Raytracer
