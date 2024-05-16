/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Keyframe.hpp
*/

#pragma once

#include "Math/Angle3D.hpp"
#include "Math/Vector3D.hpp"

#include <functional>

namespace Raytracer {
    class Keyframe {
    public:
        enum InterpolationType {
            LINEAR,
            INSTANT
        };

        Math::Vector3D pos;
        Math::Angle3D angle;

        std::pair<InterpolationType, std::function<Math::Vector3D(const Math::Vector3D &, const Math::Vector3D &, double)>> interpolationVecFunc;
        std::pair<InterpolationType, std::function<Math::Angle3D(const Math::Angle3D &, const Math::Angle3D &, double)>> interpolationAngleFunc;

        static Keyframe keyframeFactory(const Math::Vector3D &vec, const Math::Angle3D &angle,
            const std::string &linearMethodVec, const std::string &linearMethodAngle);
    };

} // namespace Raytracer
