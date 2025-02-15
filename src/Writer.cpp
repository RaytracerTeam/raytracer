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
    void WriteFile::writeImagePPM(const std::string &path,
        const sf::Image &buffer, const Dimension &dimension)
    {
        std::ofstream ofs(path + ".ppm", std::ios::out | std::ios::binary);

        ofs << "P6\n"
            << dimension.getWidth() << " " << dimension.getHeight()
            << "\n255\n";

        for (size_t y = 0; y < dimension.getHeight(); y++) {
            for (size_t x = 0; x < dimension.getWidth(); x++) {
                sf::Color pixel = buffer.getPixel(sf::Vector2u(x, y));
                ofs << pixel.r << pixel.g << pixel.b;
            }
        }
    }

    void WriteFile::writeImageJPG(const std::string &path, const sf::Image &buffer)
    {
        buffer.saveToFile(path + ".jpg");
    }

    void WriteFile::writeImagePNG(const std::string &path, const sf::Image &buffer)
    {
        buffer.saveToFile(path + ".png");
    }

    void WriteFile::writeImage(
        WriteType type, const std::string &path, const sf::Image &buffer, const Dimension &dimension)
    {
        switch (type) {
        case PPM:
            writeImagePPM(path, buffer, dimension);
            break;
        case JPG:
            writeImageJPG(path, buffer);
            break;
        case PNG:
            writeImagePNG(path, buffer);
            break;
        }
    }
} // namespace Raytracer
