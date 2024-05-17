/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** selectShootedPrimitive
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include <cmath>

namespace Raytracer
{
    void SceneInteractive::selectShootedPrimitive(void)
    {
        auto optPrim = m_scene->getPrimitiveHit(sf::Vector2i(
            m_dimension.getWidth() / 2, m_dimension.getHeight() / 2
        ));
        if (optPrim == std::nullopt)
            return;

        #ifdef BONUS
        int i = 0;
        for (auto &prim : m_scene->getPrimitives()) {
            if (prim->getID() == (*optPrim)->getID()) {
                m_selectedPrimitive = prim.get();
                IMaterial *mat = prim->getMaterial().get();
                m_selectedPrimitiveSpecular = mat->getSpecular();
                m_selectedPrimitiveShininess = mat->getShininess();
                m_selectedPrimitiveTransparency = mat->getTransparency();
                mat->setSpecular(2);
                mat->setShininess(30);
                mat->setTransparency(0.3);
                m_selectedObject = i;
                m_selectPrimitiveTab = true;
                m_needRendering = true;
                m_objectSelection = ObjectSelection::PRIMITIVE;
                break;
            }
            i++;
        }
        #endif
    }

    void SceneInteractive::releaseSelectedPrimitive(void)
    {
        #ifdef BONUS
        if (!m_selectedPrimitive)
            return;
        IMaterial *mat = m_selectedPrimitive->getMaterial().get();
        mat->setSpecular(m_selectedPrimitiveSpecular);
        mat->setShininess(m_selectedPrimitiveShininess);
        mat->setTransparency(m_selectedPrimitiveTransparency);
        m_selectedPrimitive = nullptr;
        m_needRendering = true;
        #endif
    }
    Math::Vector3D SceneInteractive::getCameraFrontPos(void)
    {
        Camera &currentCamera = m_scene->getCurrentCamera();
        Math::Angle3D angle = currentCamera.getAngle() * (M_PI / 180);
        Math::Vector3D cameraAngle(
            -sin(angle.getYaw()) * cos(angle.getPitch()),
            sin(angle.getPitch()),
            -cos(angle.getYaw()) * cos(angle.getPitch()));
        return currentCamera.getPos() + cameraAngle * m_reach;
    }
} // namespace Raytracer
