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

    Camera *Scene::getCurrentCamera(void) const
    {
        if (m_cameras.size() == 0)
            throw Error("There is no camera available", "Scene::getCurrentCamera");
        return m_cameras.at(m_curCamIndex).get();
    }

    // https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
    std::vector<Color> Scene::render(void)
    {
        Camera &camera = *getCurrentCamera();
        Dimension dimension = camera.getDimension();

        std::vector<Color> buffer(dimension.getHeight() * dimension.getWidth());
        size_t curPosBuffer = 0;

        double scale = std::tan(Math::deg2rad(camera.getFov() * 0.5));
        double imageAspectRatio = dimension.getWidthD() / dimension.getHeightD();

        for (size_t y = 0; y < dimension.getHeight(); y++) {
            for (size_t x = 0; x < dimension.getWidth(); x++) {
                double rayX = (2 * (x + 0.5) / dimension.getWidthD() - 1) * imageAspectRatio * scale;
                double rayY = (1 - 2 * (y + 0.5) / dimension.getHeightD()) * scale;
                Math::Vector3D dir = Math::Vector3D(rayX, rayY, -1).normalize().rotate(camera.getAngle());
                buffer[curPosBuffer++] = castRay(Ray(camera.getPos(), dir));
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
                    if (val == 0)
                        return Color(0., 0, 0);
                    auto primColor = prim->getColor(rayhit);
                    return Color(
                        val * primColor.getR(),
                        val * primColor.getG(),
                        val * primColor.getB());
                }
            }
        }
        return Color(0., 0, 0);
    }
} // namespace Raytracer
