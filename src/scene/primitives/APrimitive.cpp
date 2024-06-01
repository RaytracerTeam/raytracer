/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.cpp
*/

#include "Scene/Primitives/APrimitive.hpp"

namespace Raytracer {
    void APrimitive::updateTransformations(void)
    {
        m_bckOrigin = m_matrixT.applyBackward(m_origin);
        m_fwdOrigin = m_matrixT.applyForward(m_bckOrigin);
        m_bckTranslation = m_matrixT.applyBackward(m_transformations.getTranslation());
        m_fwdTranslation = m_matrixT.applyForward(m_bckTranslation);
    }
} // namespace Raytracer
