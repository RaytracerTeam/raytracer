/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editCube
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Cube.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editCube(Cube *cube)
    {
        (void)cube;
        #ifdef BONUS
        float v1[3] = { (float)cube->getVec1().getX(), (float)cube->getVec1().getY(),
            (float)cube->getVec1().getZ() };
        if (ImGui::SliderFloat3("Vector1", v1, DEFAULT_POS_MIN,
                DEFAULT_POS_MAX)) {
            cube->setVec1(Math::Vector3D(v1[0], v1[1], v1[2]));
            m_updateBVH = true;
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer
