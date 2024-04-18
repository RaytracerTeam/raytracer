/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include "Error.hpp"
#include "Math/Utils.hpp"

#include <algorithm>
#include <cmath>

// temp
#include "Primitives/Sphere.hpp"
#include <iostream>

namespace Raytracer {
    void Scene::addPrimitive(std::unique_ptr<IPrimitive> obj)
    {
        m_primitives.push_back(std::move(obj));
    }

    void Scene::addCamera(std::unique_ptr<Camera> obj)
    {
        m_cameras.push_back(std::move(obj));
    }

    void Scene::addLight(std::unique_ptr<Light> obj)
    {
        m_lights.push_back(std::move(obj));
    }

    bool Scene::setCameraIndex(size_t index)
    {
        if (index >= m_cameras.size())
            return false;
        m_curCamIndex = index;
        return true;
    }

    bool Scene::setCameraIndexRelative(int64_t offset)
    {
        if ((size_t)(std::abs(offset)) >= m_curCamIndex)
            return false;
        m_curCamIndex += offset;
        return true;
    }

    // https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
    std::vector<Color> Scene::render(void)
    {
        Camera *camera = getCurrentCamera();
        if (camera == nullptr)
            throw Error("No camera added to scene", "Scene::render");

        pixels_t dimension = camera->getDimension();

        std::vector<Color> buffer(dimension.height * dimension.width);
        size_t curPosBuffer = 0;

        double scale = std::tan(Math::deg2rad(camera->getFov() * 0.5));
        double imageAspectRatio = dimension.width / (double)dimension.height;

        // temp
        addPrimitive(std::make_unique<Sphere>(1.));
        auto val = Math::Vector3D(-10, -1.2, -18);
        m_primitives.front()->setOrigin(val);

        addLight(std::make_unique<Light>(Math::Vector3D(1, 0, -1), Color(255, 255, 255)));

        for (size_t y = 0; y < dimension.height; y++) {
            for (size_t x = 0; x < dimension.width; x++) {
                double rayX = (2 * (x + 0.5) / (double)dimension.width - 1) * imageAspectRatio * scale;
                double rayY = (1 - 2 * (y + 0.5) / (double)dimension.height) * scale;
                Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize();
                buffer[curPosBuffer++] = castRay(Ray(camera->getPos(), dir));
            }
        }
        return buffer;
    }

    Color Scene::castRay(const Ray &ray)
    {
        for (auto &prim : m_primitives) {
            RayHit rayhit = prim->hit(ray);
            if (rayhit.isHit()) {
                for (auto &light : m_lights) {
                    double val = std::max(
                        rayhit.getNormal().dot(-light->getOrigin()),
                        0.);

                    // temp, but average this each lights
                    // purple shading
                    if (val == 0)
                        return Color();
                    return Color(val * Color::RGBToPercent(204), 0, val * Color::RGBToPercent(204));
                }
            }
            // return { 255, 200, 0, 50 }; // unreachable
        }
        return { 0, 0, 0 };
    }
} // namespace Raytracer
