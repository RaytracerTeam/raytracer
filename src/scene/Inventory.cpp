/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Inventory.cpp
*/

#include "Scene/Inventory.hpp"

namespace Raytracer {
    Inventory::Inventory()
    {
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(1., 1, 1))); // 0
        m_materials.push_back(std::make_unique<CubeTexture>("assets/textures/minecraft/cobblestone.png")); // 1
        m_materials.push_back(std::make_unique<CubeTexture>("assets/textures/minecraft/old_grass_block.png")); // 2
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(0., 0, 0))); // 3
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(1., 0, 0))); // 4
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(0., 1, 0))); // 5
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(0., 0, 1))); // 6
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(0., 1, 1))); // 7
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(1., 0, 1))); // 8
        m_materials.push_back(std::make_unique<MaterialSolid>(Color(1., 1, 0))); // 9
    }

    void Inventory::setMaterial(size_t index, std::unique_ptr<IMaterial> material)
    {
        if (index >= m_materials.size())
            m_materials.push_back(std::move(material));
        else
            m_materials[index] = std::move(material);
    }
} // namespace Raytracer
