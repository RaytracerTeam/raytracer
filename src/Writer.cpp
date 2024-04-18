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
        const size_t imgSize = height * width;

        if (type == PNG)
            bernard.saveToFile("./out");
        ofs << "P6\n"
            << width << " " << height << "\n255\n";
        for (size_t i = 0; i < imgSize; i++) {
            char r = (char)(Color::PercentToRGB(buffer[i][0]));
            char g = (char)(Color::PercentToRGB(buffer[i][1]));
            char b = (char)(Color::PercentToRGB(buffer[i][2]));
            ofs << r << g << b;
        }
    }
} // namespace Raytracer
