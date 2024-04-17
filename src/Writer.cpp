/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Writer.cpp
*/

#include "Writer.hpp"

#include <iostream>
#include <algorithm>
#include <fstream>

namespace Raytracer {
    void WriteFile::writeImage(WriteType type, std::vector<bool> buffer,
        size_t width, size_t height)
    {
        std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);

        ofs << "P6\n" << width << " " << height << "\n255\n";
        for (size_t i = 0; i < height * width; i++) {
            char r = (char)(255 * std::clamp(0, 1, (int)buffer[i]));
            char g = (char)(255 * std::clamp(0, 1, (int)buffer[i]));
            char b = (char)(255 * std::clamp(0, 1, (int)buffer[i]));
            ofs << r << g << b;
        }
    }
} // namespace Raytracer
