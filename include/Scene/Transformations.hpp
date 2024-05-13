/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Transformations
*/

#pragma once

#include "Math/Vector3D.hpp"

namespace Raytracer {
    class Transformations {
    public:
        Transformations()
            : m_translation(0, 0, 0)
            , m_rotation(0, 0, 0)
            , m_scale(1, 1, 1)
        {
        }
        Transformations(const Math::Vector3D &translation, const Math::Vector3D &rotation, const Math::Vector3D &scale)
            : m_translation(translation)
            , m_rotation(rotation)
            , m_scale(scale)
        {
        }
        ~Transformations() = default;

        void setTranslation(const Math::Vector3D &translation) { m_translation = translation; }
        void setRotation(const Math::Vector3D &rotation) { m_rotation = rotation; }
        void setScale(const Math::Vector3D &scale) { m_scale = scale; }

        const Math::Vector3D &getTranslation(void) const { return m_translation; }
        const Math::Vector3D &getRotation(void) const { return m_rotation; }
        const Math::Vector3D &getScale(void) const { return m_scale; }

    private:
        Math::Vector3D m_translation;
        Math::Vector3D m_rotation;
        Math::Vector3D m_scale;
    };
}
