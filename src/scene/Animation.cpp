/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Animation.cpp
*/

#include "Scene/Animation.hpp"
#include "Parsing/Parsing.hpp"
#include "Raytracer.hpp"

#include <functional>
#include <sstream>
#include <unordered_map>

namespace Raytracer {

    template <typename T>
    static const std::unordered_map<std::string, std::pair<Keyframe::InterpolationType, std::function<T(const T &, const T &, double)>>> INTERPOLAITON_FACTORY = {
        { "linear", { Keyframe::LINEAR, [](const T &v0, const T &v1, double t) { return v0 + (v1 - v0) * t; } } },
        { "instant", { Keyframe::INSTANT, [](const T &, const T &v1, double) { return v1; } } }
    };

    Keyframe Keyframe::keyframeFactory(const Math::Vector3D &vec, const Math::Angle3D &angle,
        const std::string &linearMethodVec, const std::string &linearMethodAngle)
    {
        auto funcVec = INTERPOLAITON_FACTORY<Math::Vector3D>.find(linearMethodVec);
        auto funcAngle = INTERPOLAITON_FACTORY<Math::Angle3D>.find(linearMethodAngle);

        if (funcVec == INTERPOLAITON_FACTORY<Math::Vector3D>.end() || funcAngle == INTERPOLAITON_FACTORY<Math::Angle3D>.end())
            throw Error("Invalid interpolation name functions", "Keyframe::keyframeFactory");

        return { vec, angle, funcVec->second, funcAngle->second };
    }

    Animation::Animation(const std::string &path, std::unique_ptr<Scene> scene, const Dimension &dim)
        : m_path(path)
        , m_scene(std::move(scene))
        , m_dim(dim)
    {
    }

    void Animation::screenshot(Camera &camera, const Keyframe &keyframe, const Math::Vector3D &curVec, const Math::Angle3D &curAngle, double tick, size_t &iteration, WriteFile::WriteType type, size_t maxImages)
    {
        auto vecIt = keyframe.interpolationVecFunc.second(curVec, keyframe.pos, tick);
        auto angleIt = keyframe.interpolationAngleFunc.second(curAngle, keyframe.angle, tick);
        camera.setPos(vecIt);
        camera.setAngle(angleIt);

        m_scene->render();
        m_scene->waitRendering(iteration, maxImages);

        std::stringstream ss;
        ss << iteration;
        WriteFile::writeImage(type, m_path + ss.str(), m_scene->getRender(), m_dim);
        iteration++;
    }

    void Animation::render(WriteFile::WriteType type)
    {
        const std::vector<Keyframe> &keyframes = m_scene->getCameraKeyframes();
        const size_t nbTicks = m_scene->getKeyframesTick();
        const double tickIter = 1 / (double)(nbTicks);
        Camera &camera = m_scene->getCurrentCamera();

        Math::Vector3D curVec = camera.getDefaultPos();
        Math::Angle3D curAngle = camera.getDefaultAngle();

        size_t maxImages = 0;
        for (const auto &keyframe : keyframes) {
            if (keyframe.interpolationVecFunc.first == Keyframe::INSTANT
                && keyframe.interpolationAngleFunc.first == Keyframe::INSTANT)
                maxImages++;
            else
                maxImages += nbTicks;
        }

        for (size_t i = 0; const auto &keyframe : keyframes) {
            if (keyframe.interpolationVecFunc.first == Keyframe::INSTANT
                && keyframe.interpolationAngleFunc.first == Keyframe::INSTANT) {
                screenshot(camera, keyframe, curVec, curAngle, tickIter, i, type, maxImages);
                curVec = keyframe.pos;
                curAngle = keyframe.angle;
                continue;
            }
            for (double tick = 0; tick <= 1.; tick += tickIter)
                screenshot(camera, keyframe, curVec, curAngle, tick, i, type, maxImages);
            curVec = keyframe.pos;
            curAngle = keyframe.angle;
        }
    }
} // namespace Raytracer
