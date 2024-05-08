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
#include <SFML/Graphics/Image.hpp>

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
        static void writeImage(WriteType type, const sf::Image &buffer, const Dimension &dimension);

    private:
        static void writeImagePPM(const sf::Image &buffer, const Dimension &dimension);
        static void writeImageJPG(const sf::Image &buffer);
        static void writeImagePNG(const sf::Image &buffer);
    };
} // namespace Raytracer
