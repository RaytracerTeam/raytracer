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

namespace Raytracer {
    void WriteFile::writeImagePPM(
        const sf::Image &buffer, const Dimension &dimension)
    {
        std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);

        ofs << "P6\n"
            << dimension.getWidth() << " " << dimension.getHeight()
            << "\n255\n";

        for (size_t y = 0; y < dimension.getHeight(); y++) {
            for (size_t x = 0; x < dimension.getWidth(); x++) {
                sf::Color pixel = buffer.getPixel(x, y);
                ofs << pixel.r << pixel.g << pixel.b;
            }
        }
    }

    void WriteFile::writeImageJPG(const sf::Image &buffer)
    {
        buffer.saveToFile("./out.jpg");
    }

    void WriteFile::writeImagePNG(const sf::Image &buffer)
    {
        buffer.saveToFile("./out.png");
    }

    void WriteFile::writeImage(
        WriteType type, const sf::Image &buffer, const Dimension &dimension)
    {
        switch (type) {
        case PPM:
            writeImagePPM(buffer, dimension);
            break;
        case JPG:
            writeImageJPG(buffer);
            break;
        case PNG:
            writeImagePNG(buffer);
            break;
        }
    }
} // namespace Raytracer
