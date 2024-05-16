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

    void SceneInteractive::showCrosshair(void)
    {
        const sf::Image &img = m_scene->getRender();
        const sf::Vector2u &size = img.getSize();
        sf::Vector2u center = sf::Vector2u(size.x / 2, size.y / 2);

        unsigned int crosshairSize = size.x / 50;
        unsigned int lineSize = crosshairSize / 20;
        if (crosshairSize == 0)
            crosshairSize = 1;

        for (unsigned int y = center.y - crosshairSize; y <= center.y + crosshairSize; y++) {
            for (unsigned int x = center.x - crosshairSize; x <= center.x + crosshairSize; x++) {
                if (y <= center.y + lineSize && y >= center.y - lineSize
                && x <= center.x + lineSize && x >= center.x - lineSize)
                    m_scene->setRenderPixel(x, y, Color(200U, 255, 200));
                else if ((y <= center.y + lineSize && y >= center.y - lineSize) ||
                (x <= center.x + lineSize && x >= center.x - lineSize))
                    m_scene->setRenderPixel(x, y, Color(255U, 255, 255));
            }
        }
    }
} // namespace Raytracer
