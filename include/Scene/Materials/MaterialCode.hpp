/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MaterialCode.hpp
*/

#pragma once

#include "AMaterial.hpp"

namespace Raytracer {
    class MaterialCode : public AMaterial {
    protected:
        MaterialCode(size_t factor);
        ~MaterialCode() = default;

        MaterialType getType() const override { return MaterialType::CODE; }

        size_t m_factor;
    };
} // namespace Raytracer
