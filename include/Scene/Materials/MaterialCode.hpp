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
    public :
        MaterialCode(float factor);
        ~MaterialCode() = default;

        MaterialType getType() const override { return MaterialType::CODE; }

        float getFactor() const { return m_factor; }
        float setFactor(float factor) { m_factor = factor; }
    protected:
        float m_factor;
    };
} // namespace Raytracer
