/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** minecraft
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialTexture/CubeTexture.hpp"

namespace Raytracer
{
    void SceneInteractive::minecraftPlaceBlock(void)
    {
        if (!m_useMouse)
            return;
        auto optPrim = m_scene->getIntersectionHit(sf::Vector2i(
            m_dimension.getWidth() / 2, m_dimension.getHeight() / 2
        ));
        if (!optPrim.has_value())
            return;
        const IPrimitive *prim = (*optPrim).primitve;
        RayHit rhitPrim = (*optPrim).rayhit;
        if (prim->getType() != PrimitiveType::CUBE)
            return;
        const Cube *cube = static_cast<const Cube *>(prim);

        Math::Vector3D normalScaled = rhitPrim.getNormal() * (cube->getVec1() - cube->getOrigin());

        std::unique_ptr<Cube> newCube = std::make_unique<Cube>(
            cube->getOrigin() + normalScaled,
            std::make_unique<CubeTexture>("assets/textures/minecraft/cobblestone.png"),
            cube->getVec1() + normalScaled
        );
        newCube->setID(m_scene->getPrimitives().size() + 1);
        m_scene->addPrimitive(std::move(newCube));
        m_updateBVH = true;
        m_needRendering = true;
    }

    void SceneInteractive::minecraftDestroyBlock(void)
    {
        if (!m_useMouse)
            return;
        auto optPrim = m_scene->getIntersectionHit(sf::Vector2i(
            m_dimension.getWidth() / 2, m_dimension.getHeight() / 2
        ));
        if (!optPrim.has_value())
            return;
        const IPrimitive *prim = (*optPrim).primitve;
        if (prim->getType() != PrimitiveType::CUBE)
            return;
        int i = 0;
        for (auto &prim : m_scene->getPrimitives()) {
            if (prim->getID() == (*optPrim).primitve->getID()) {
                prim->setDieASAP(true);
                m_updateBVH = true;
                m_needRendering = true;
                break;
            }
            i++;
        }
    }
} // namespace Raytracer
