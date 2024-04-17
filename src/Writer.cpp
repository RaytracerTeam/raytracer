/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Writer.cpp
*/

#include "Writer.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <SFML/Graphics/Image.hpp>

namespace Raytracer {
    void WriteFile::writeImage(WriteType type, std::vector<Color> buffer,
        size_t width, size_t height)
    {
        std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
        sf::Image bernard;

        if (type == PNG)
            bernard.saveToFile("./out");
        ofs << "P6\n"
            << width << " " << height << "\n255\n";
        for (size_t i = 0; i < height * width; i++) {
            char r = (char)(255 * std::clamp(0, 1, (int)(buffer[i].r)));
            char g = (char)(255 * std::clamp(0, 1, (int)(buffer[i].g)));
            char b = (char)(255 * std::clamp(0, 1, (int)(buffer[i].b)));
            ofs << r << g << b;
        }
    }
} // namespace Raytracer
