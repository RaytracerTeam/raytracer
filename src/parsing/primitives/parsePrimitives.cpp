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
        void parsePrimitives(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists("primitives"))
                return;

            const libconfig::Setting &primitiveSetting = config.lookup("primitives");

            parseSpheres(primitiveSetting, scene);
            parsePlanes(primitiveSetting, scene);
            parseCylinders(primitiveSetting, scene);
            parseCones(primitiveSetting, scene);
        }
    } // namespace Parsing
} // namespace Raytracer
