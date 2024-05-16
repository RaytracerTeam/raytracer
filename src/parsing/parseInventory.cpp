/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseMaterial
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Inventory.hpp"

namespace Raytracer {
    namespace Parsing {
        void parseInventory(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_INVENTORY))
                return;
        }
    } // namespace Parsing
} // namespace Raytracer
