/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Raytracer.cpp
*/

#include "Raytracer.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Interactive/SceneInteractive.hpp"
#include "Writer.hpp"

#include <string.h>

// temp
#include "Primitives/Sphere.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Cylinder.hpp"

namespace Raytracer {
    static int interactive(Scene *scene, Dimension &screnDim, const double fov)
    {
        std::unique_ptr<SceneInteractive> interact = std::make_unique<SceneInteractive>(
            screnDim,
            "Raytracer");
        scene->addCamera(std::make_unique<Camera>(screnDim, fov));

        // temp
        auto sphere = std::make_unique<Sphere>(1.);
        sphere->setOrigin(Math::Vector3D(-1, -1.2, -18));
        sphere->setSolidColor(Color(200U, 0U, 200U));
        scene->addPrimitive(std::move(sphere));

        auto sphere2 = std::make_unique<Sphere>(3.);
        sphere2->setOrigin(Math::Vector3D(1, 1, -10));
        sphere2->setSolidColor(Color(200U, 150U, 0U));
        scene->addPrimitive(std::move(sphere2));

        // auto cyl = std::make_unique<Cylinder>(1., std::numeric_limits<double>::infinity());
        auto cyl = std::make_unique<Cylinder>(1., 1.);
        cyl->setOrigin(Math::Vector3D(-2, 0, -10));
        cyl->setSolidColor(Color(0U, 150U, 200U));
        scene->addPrimitive(std::move(cyl));

        auto plane = std::make_unique<Plane>(-4, Plane::Y);
        plane->setSolidColor(Color(200U, 0U, 0U));
        scene->addPrimitive(std::move(plane));

        scene->addLight(std::make_unique<Light>(Math::Vector3D(1, 0, -1), Color(255U, 255U, 255U)));
        scene->updatePrimitives();
        //

        interact->setScene(scene);
        interact->loop();
        return 0;
    }

    static int imageOutput(Scene *scene, Dimension &screnDim, const double fov)
    {
        scene->addCamera(std::make_unique<Camera>(screnDim, fov));

        // temp
        auto sphere = std::make_unique<Sphere>(1.);
        sphere->setOrigin(Math::Vector3D(-1, -1.2, -18));
        sphere->setSolidColor(Color(200U, 0U, 200U));
        scene->addPrimitive(std::move(sphere));

        auto sphere2 = std::make_unique<Sphere>(3.);
        sphere2->setOrigin(Math::Vector3D(1, 1, -10));
        sphere2->setSolidColor(Color(200U, 150U, 0U));
        scene->addPrimitive(std::move(sphere2));

        auto plane = std::make_unique<Plane>();
        plane->setOrigin(Math::Vector3D(0, -4, 0));
        plane->setAxis(Plane::Y);
        plane->setSolidColor(Color(200U, 0U, 0U));
        scene->addPrimitive(std::move(plane));

        scene->addLight(std::make_unique<Light>(Math::Vector3D(1, 0, -1), Color(255U, 255U, 255U)));
        //

        auto res = scene->render();
        WriteFile::writeImage(WriteFile::PPM, res, screnDim);
        return 0;
    }

    int raytracer(int argc, char **argv)
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>();
        Dimension dimension(640, 480);
        const double fov = 51.52;
        // struct {size_t x; size_t y;} screnDim = {640, 480};
        // struct {size_t x; size_t y;} screnDim = {1920, 1080};

        if (argc == 2 && strcmp(argv[1], "-i") == 0)
            return interactive(scene.get(), dimension, fov);
        return imageOutput(scene.get(), dimension, fov);
    }
}
