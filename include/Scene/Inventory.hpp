/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Inventory.hpp
*/

#pragma once

#include "Scene/Materials/AllMaterials.hpp"

namespace Raytracer {
    class Inventory {
    public:
        Inventory();
        ~Inventory() = default;

        void setCurrentMaterialIndex(size_t index) { m_currentMaterialIndex = index; }
        void setCurrentMaterial(std::unique_ptr<IMaterial> material) { m_materials[m_currentMaterialIndex] = std::move(material); }
        void addMaterial(std::unique_ptr<IMaterial> material) { m_materials.push_back(std::move(material)); }

        const std::vector<std::unique_ptr<IMaterial>> &getMaterials(void) const { return m_materials; }
        size_t getCurrentMaterialIndex(void) const { return m_currentMaterialIndex; }
        std::unique_ptr<IMaterial> &getCurrentMaterial(void) { return m_materials[m_currentMaterialIndex]; }
        std::unique_ptr<IMaterial> getCurrentMaterialCopy(void) { return std::move(m_materials[m_currentMaterialIndex]); }

    private:
        std::vector<std::unique_ptr<IMaterial>> m_materials;
        size_t m_currentMaterialIndex = 0;
    };
} // namespace Raytracer

