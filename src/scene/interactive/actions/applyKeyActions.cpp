/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** applyKeyActions
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Math/Algorithm.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::applyActions(void)
    {
        Camera *camera = m_interacCam.getCamera();
        auto camPos = camera->getPos();
        auto camAngle = camera->getAngle();
        auto movementCamAngle = camAngle;
        movementCamAngle.setPitch(0);

        if (m_actions[SceneAction::MOVE_FORWARD].second) {
            camPos += Math::Vector3D(0, 0, -m_movementSpeed).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_BACKWARD].second) {
            camPos += Math::Vector3D(0, 0, m_movementSpeed).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_LEFT].second) {
            camPos += Math::Vector3D(-m_movementSpeed, 0, 0).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_RIGHT].second) {
            camPos += Math::Vector3D(m_movementSpeed, 0, 0).rotate(movementCamAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_UP].second) {
            camPos += Math::Vector3D(0, m_movementSpeed, 0);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::MOVE_DOWN].second) {
            camPos += Math::Vector3D(0, -m_movementSpeed, 0);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_UP].second) {
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() + m_rotationSpeed, -90., 90.));
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_DOWN].second) {
            camAngle.setPitch(Math::Algorithm::clampD(camAngle.getPitch() - m_rotationSpeed, -90., 90.));
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_LEFT].second) {
            camAngle.setYaw(camAngle.getYaw() + m_rotationSpeed);
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::ROTATE_RIGHT].second) {
            camAngle.setYaw(camAngle.getYaw() - m_rotationSpeed);
            camera->setAngle(camAngle);
            m_needRendering = true;
        }
        if (m_actions[SceneAction::SPRINT].second) {
            m_movementSpeed = m_defaultMovementSpeed * 4;
        } else {
            m_movementSpeed = m_defaultMovementSpeed;
        }
        if (m_actions[SceneAction::PAINT].second) {
            auto sphere = std::make_unique<Sphere>(
                getCameraFrontPos(),
                copyMaterial(m_scene->getInventory().getCurrentMaterial().get()),
                Transformations(),
                1.0);
            sphere->setID(m_scene->getPrimitives().size() + 1);
            m_scene->addPrimitive(std::move(sphere));
            m_needRendering = true;
            m_updateBVH = true;
        }
        camera->setPos(camPos);
    }
} // namespace Raytracer
