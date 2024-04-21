/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.cpp
*/

#include "Scene/Scene.hpp"
#include "Error.hpp"
#include "Math/Utils.hpp"

#include <algorithm>
#include <cmath>

namespace Raytracer {
    void Scene::addPrimitive(std::unique_ptr<IPrimitive> obj)
    {
        m_primitives.push_back(std::move(obj));
    }

    void Scene::addCamera(std::unique_ptr<Camera> obj)
    {
        m_cameras.push_back(std::move(obj));
    }

    void Scene::addLight(std::unique_ptr<ILight> obj)
    {
        m_lightSystem.addLight(std::move(obj));
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

    Camera &Scene::getCurrentCamera(void) const
    {
        if (m_cameras.size() == 0)
            throw Error("There is no camera available", "Scene::getCurrentCamera");
        return *m_cameras.at(m_curCamIndex).get();
    }

    // https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
    std::vector<Color> Scene::render(void)
    {
        Camera &camera = getCurrentCamera();
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

    /* call this whenever the camera updates */
    void Scene::updatePrimitives(void)
    {
        auto cameraPos = getCurrentCamera().getPos();

        std::sort(
            begin(m_primitives),
            end(m_primitives),
            [cameraPos](const std::unique_ptr<IPrimitive> &lhs, const std::unique_ptr<IPrimitive> &rhs) {
                return Math::Vector3D::gDist(cameraPos, lhs->getOrigin()) < Math::Vector3D::gDist(cameraPos, rhs->getOrigin());
            });
    }

    Color Scene::castRay(const Ray &ray) const
    {
        for (auto &prim : m_primitives) {
            std::optional<RayHit> rayhit = prim->hit(ray);
            if (rayhit == std::nullopt)
                continue;

            auto primMaterial = prim->getMaterial();
            auto primColor = primMaterial->getColor(rayhit.value());
            return Color(
                primColor.getR(),
                primColor.getG(),
                primColor.getB());
        }
        return Color(0., 0, 0);
    }
} // namespace Raytracer
