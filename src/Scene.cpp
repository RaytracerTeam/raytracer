/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include "Error.hpp"
#include "Math/Utils.hpp"
#include "Math/Matrix44d.hpp"

#include <cmath>

// temp
#include "Primitives/Sphere.hpp"

namespace Raytracer {
    void Scene::addPrimitive(std::unique_ptr<IPrimitive> obj)
    {
        m_primitives.push_back(std::move(obj));
    }

    void Scene::addCamera(std::unique_ptr<Camera> obj)
    {
        m_cameras.push_back(std::move(obj));
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
    std::vector<bool> Scene::render(void)
    {
        Camera *camera = getCurrentCamera();
        if (camera == nullptr)
            throw Error("No camera added to scene", "Scene::render");

        pixels_t dimension = camera->getDimension();

        std::vector<bool> buffer(dimension.height * dimension.width);
        size_t curPosBuffer = 0;

        double scale = std::tan(Math::deg2rad(camera->getFov() * 0.5));
        double imageAspectRatio = dimension.width / (double)dimension.height;

        // temp
        addPrimitive(std::make_unique<Sphere>(1.));
        auto val = Math::Point3D(3, 0, 3);
        m_primitives.front()->setOrigin(val);

        Math::Matrix44 mat;
        mat[0][0] = 0.945519;
        mat[0][1] = 0;
        mat[0][2] = -0.325569;
        mat[0][3] = 0;
        mat[1][0] = -0.179534;
        mat[1][1] = 0.834209;
        mat[1][2] = -0.521403;
        mat[1][3] = 0;
        mat[2][0] = 0.271593;
        mat[2][1] = 0.551447;
        mat[2][2] = 0.78876;
        mat[2][3] = 0.78876;
        mat[3][0] = 4.208271;
        mat[3][1] = 8.374532;
        mat[3][2] = 17.932925;
        mat[3][3] = 1;
        auto camPos = mat * camera->getPos();

        for (size_t y = 0; y < dimension.height; y++) {
            for (size_t x = 0; x < dimension.width; x++) {
                double rayX = (2 * (x + 0.5) / (double)dimension.width - 1) * imageAspectRatio * scale;
                double rayY = (1 - 2 * (y + 0.5) / (double)dimension.height) * scale;
                Math::Vector3D dir = mat * Math::Vector3D(rayX, rayY, -1);
                buffer[curPosBuffer++] = castRay(Ray(camPos, dir));
            }
        }
        return buffer;
    }

    bool Scene::castRay(const Ray &ray)
    {
        for (auto &prim : m_primitives) {
            if (prim->hit(ray))
                return true;
        }
        return false;
    }
} // namespace Raytracer
