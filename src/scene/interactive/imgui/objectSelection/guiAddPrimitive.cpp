/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiAddPrimitive
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::guiAddPrimitive(void)
    {
        if (ImGui::BeginCombo(" ", "Add Primitive")) {
            if (ImGui::Selectable("Sphere")) {
                auto sphere = std::make_unique<Sphere>(
                    Math::Vector3D(0, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    1.0);
                sphere->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(sphere));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Plane")) {
                auto plane = std::make_unique<Plane>(
                    -10.0,
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    Plane::Axis::Y);
                plane->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(plane));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Cylinder")) {
                auto cylinder = std::make_unique<Cylinder>(
                    Math::Vector3D(0, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    1.0,
                    1.0);
                cylinder->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(cylinder));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Cone")) {
                auto cone = std::make_unique<Cone>(
                    Math::Vector3D(0, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    1.0,
                    1.0);
                cone->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(cone));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Torus")) {
                auto torus = std::make_unique<Torus>(
                    Math::Vector3D(0, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    0.5,
                    1.0);
                torus->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(torus));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Tanglecube")) {
                auto tanglecube = std::make_unique<Tanglecube>(
                    Math::Vector3D(0, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    11.8);
                tanglecube->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(tanglecube));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Triangle")) {
                auto triangle = std::make_unique<Triangle>(
                    Math::Vector3D(1, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    Math::Vector3D(0, 1, 0),
                    Math::Vector3D(0, 0, 1));
                triangle->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(triangle));
                m_needRendering = true;
                m_updateBVH = true;
            }
            if (ImGui::Selectable("Cube")) {
                auto cube = std::make_unique<Cube>(
                    Math::Vector3D(0, 0, 0),
                    std::make_unique<MaterialSolid>(
                        Color((unsigned int)255, 255, 255)),
                    Math::Vector3D(1, 1, 1));
                cube->setID(m_scene->getPrimitives().size() + 1);
                m_scene->addPrimitive(std::move(cube));
                m_needRendering = true;
                m_updateBVH = true;
            }
            ImGui::EndCombo();
        }
    }
} // namespace Raytracer
