/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parsePrimitives
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer {
    namespace Parsing
    {
        void parsePrimitives(const libconfig::Config &config, Scene &scene)
        {
            if (!config.exists("primitives"))
                return;

            const libconfig::Setting &primitiveSetting = config.lookup("primitives");

            parseSphere(primitiveSetting, scene);
            parsePlane(primitiveSetting, scene);
        }
    } // namespace Parsing
} // namespace Raytracer
