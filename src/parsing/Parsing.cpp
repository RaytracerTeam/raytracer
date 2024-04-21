/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.cpp
*/

#include "Parsing/Parsing.hpp"

// temp
#include "Scene/Primitives/Cylinder.hpp"
#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

#include "Scene/Lights/PointLight.hpp"

namespace Raytracer {
    namespace Parsing {
        void parse(Scene &scene, const Dimension &dim, const std::string &)
        {
            // TEMP
            scene.addCamera(std::make_unique<Camera>(dim, 51.82));

            // temp
            auto sphere = std::make_unique<Sphere>(Math::Vector3D(-1, 1, -18), std::make_unique<MaterialSolid>(Color(200U, 0U, 200U)), 1.);
            scene.addPrimitive(std::move(sphere));

            auto sphere2 = std::make_unique<Sphere>(Math::Vector3D(-1, 1, -10), std::make_unique<MaterialSolid>(Color(200U, 150U, 0U)), 3.);
            scene.addPrimitive(std::move(sphere2));

            // auto cyl = std::make_unique<Cylinder>(1., std::numeric_limits<double>::infinity());
            // auto cyl = std::make_unique<Cylinder>(Math::Vector3D(-2, 0, -10), std::make_unique<MaterialSolid>(Color(0U, 150U, 200U)), 1., 1.);
            // scene.addPrimitive(std::move(cyl));

            auto plane = std::make_unique<Plane>(-4, std::make_unique<MaterialSolid>(Color(200U, 0, 0)), Plane::Y);
            scene.addPrimitive(std::move(plane));

            scene.addLight(std::make_unique<PointLight>(Math::Vector3D(-1, 0, -1), Color(255U, 255U, 255U), 0.75));
            scene.addLight(std::make_unique<PointLight>(Math::Vector3D(1, 8, -6), Color(0U, 0U, 200U), 0.9));
        }
    } // namespace Parsing

} // namespace Raytracer
