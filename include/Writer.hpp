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

namespace Raytracer {
    class WriteFile {
    public:
        struct PPMObject {
            std::string magicNum;
            size_t width;
            size_t height;
            size_t maxColVal;
            char *m_Ptr;
        };

        enum WriteType {
            PPM,
            JPG,
            PNG
        };
        static void writeImage(WriteType type, std::vector<Color> buffer, size_t width, size_t height);
    };
} // namespace Raytracer
