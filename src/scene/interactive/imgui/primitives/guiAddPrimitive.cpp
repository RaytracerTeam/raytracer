/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiAddPrimitive
*/

#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer
{
    void SceneInteractive::guiAddPrimitive(void)
    {
        if (ImGui::BeginCombo(" ", "Add Primitive")) {
            IMaterial *currentMaterial = m_scene->getInventory().getCurrentMaterial().get();
            if (ImGui::Selectable("Sphere")) {
                auto sphere = std::make_unique<Sphere>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    1.0);
                sphere->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(sphere));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Plane")) {
                auto plane = std::make_unique<Plane>(
                    getCameraFrontPos()[1] - 10,
                    copyMaterial(currentMaterial),
                    Plane::Axis::Y);
                plane->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(plane));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Cylinder")) {
                auto cylinder = std::make_unique<Cylinder>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    1.0,
                    1.0);
                cylinder->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(cylinder));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Cone")) {
                auto cone = std::make_unique<Cone>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    1.0,
                    1.0);
                cone->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(cone));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Torus")) {
                auto torus = std::make_unique<Torus>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    0.5,
                    1.0);
                torus->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(torus));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Tanglecube")) {
                auto tanglecube = std::make_unique<Tanglecube>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    11.8);
                tanglecube->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(tanglecube));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Triangle")) {
                auto triangle = std::make_unique<Triangle>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    getCameraFrontPos() + Math::Vector3D(0, 2, 0),
                    getCameraFrontPos() + Math::Vector3D(0, 0, 2));
                triangle->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(triangle));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Cube")) {
                auto cube = std::make_unique<Cube>(
                    getCameraFrontPos(),
                    copyMaterial(currentMaterial),
                    getCameraFrontPos() + Math::Vector3D(1, 1, 1));
                cube->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(cube));
                m_needRendering = true;
                m_updateBVH = true;
            }
            ImGui::EndCombo();
        }
    }
} // namespace Raytracer
