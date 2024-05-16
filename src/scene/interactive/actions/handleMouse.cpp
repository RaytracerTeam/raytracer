/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** sceneInterationsActions
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Math/Algorithm.hpp"

namespace Raytracer
{
    void SceneInteractive::handleMouse(void)
    {
        Camera &currentCamera = m_scene->getCurrentCamera();

        float sensivity = m_rotationSpeed / 10;

        if (m_useSimpleMouse) {
            auto pos = sf::Mouse::getPosition();
            auto delta = pos - m_lastMousePos;
            if (delta.x == 0 && delta.y == 0)
                return;
            auto angle = currentCamera.getAngle();
            angle.setYaw(angle.getYaw() - delta.x * sensivity);
            angle.setPitch(Math::Algorithm::clampD(angle.getPitch() - delta.y * sensivity, -90., 90.));
            currentCamera.setAngle(angle);
            m_needRendering = true;
            m_lastMousePos = pos;
        }

        else if (m_useMouse) {
            if (m_mouseCentered > 1) {
                m_mouseCentered--;
                return;
            }
            if (m_mouseCentered == 1) {
                m_mouseCenterCorrection = sf::Mouse::getPosition() - MOUSE_CENTER;
                m_mouseCentered = 0;
            }

            auto pos = sf::Mouse::getPosition();
            auto delta = pos - MOUSE_CENTER;
            delta -= m_mouseCenterCorrection;
            if (delta.x == 0 && delta.y == 0)
                return;
            sf::Mouse::setPosition(MOUSE_CENTER);
            auto angle = currentCamera.getAngle();
            angle.setYaw(angle.getYaw() - delta.x * sensivity);
            angle.setPitch(Math::Algorithm::clampD(angle.getPitch() - delta.y * sensivity, -90., 90.));
            currentCamera.setAngle(angle);
            m_needRendering = true;
        }
    }
} // namespace Raytracer
