/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveInventory
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Inventory.hpp"

namespace Raytracer
{
    void Parsing::saveInventory(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &inventorySetting = root.add(CFG_INVENTORY, libconfig::Setting::TypeList);
        const Inventory &inventory = scene.getInventory();
        for (const auto &item : inventory.getMaterials()) {
            libconfig::Setting &setting = inventorySetting.add(libconfig::Setting::TypeGroup);
            setting.add(CFG_MATERIAL_TYPE, libconfig::Setting::TypeString) = item->getTypeString();
            saveMaterial(setting, item);
        }
    }
} // namespace Raytracer
