/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editTriangle
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Triangle.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editTriangle(Triangle *triangle)
    {
        float v1[3] = { (float)triangle->getVec1().getX(), (float)triangle->getVec1().getY(),
            (float)triangle->getVec1().getZ() };
        if (ImGui::SliderFloat3("Vector1", v1, DEFAULT_POS_MIN,
                DEFAULT_POS_MAX)) {
            triangle->setVec1(Math::Vector3D(v1[0], v1[1], v1[2]));
            m_updateBVH = true;
            m_needRendering = true;
        }

        float v2[3] = { (float)triangle->getVec2().getX(), (float)triangle->getVec2().getY(),
            (float)triangle->getVec2().getZ() };
        if (ImGui::SliderFloat3("Vector2", v2, DEFAULT_POS_MIN,
                DEFAULT_POS_MAX)) {
            triangle->setVec2(Math::Vector3D(v2[0], v2[1], v2[2]));
            m_updateBVH = true;
            m_needRendering = true;
        }
    }
} // namespace Raytracer
