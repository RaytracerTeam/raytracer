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
        static MaterialType getMaterialType(const libconfig::Setting &setting)
        {
            if (!setting.exists(CFG_MATERIAL_TYPE))
                return MaterialType::NONE;
            std::string type = setting.lookup(CFG_MATERIAL_TYPE);
            for (size_t i = 0; i < (size_t)MaterialType::SIZE; i++) {
                if (MaterialTypeStrings[i] == type)
                    return static_cast<MaterialType>(i);
            }
            return MaterialType::NONE;
        }
        void parseInventory(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_INVENTORY))
                return;

            const libconfig::Setting &inventorySetting = config.lookup(CFG_INVENTORY);
            Inventory &inventory = scene->getInventory();
            int i = 0;
            for (const auto &inventorySetting : inventorySetting) {
                inventory.setMaterial(i, parseMaterial(inventorySetting, getMaterialType(inventorySetting)));
                i++;
            }
        }
    } // namespace Parsing
} // namespace Raytracer
