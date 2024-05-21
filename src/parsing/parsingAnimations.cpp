/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** parsingAnimations.cpp
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Keyframe.hpp"

namespace Raytracer {
    namespace Parsing {
        static void parseKeyframe(const libconfig::Setting &setting, std::unique_ptr<Scene> &scene)
        {
            Math::Vector3D pos = parsePosition(setting);
            Math::Angle3D angle = getSettingRotation(setting);

            try {
                auto interpolationVec = setting.lookup("interVec").c_str();
                auto interpolationAngle = setting.lookup("interAngle").c_str();

                auto keyframe = Keyframe::keyframeFactory(pos, angle, interpolationVec, interpolationAngle);
                scene->addKeyframe(keyframe);
            } catch (std::exception &) {
                return;
            }
        }

        void parseAnimations(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_ANIMATIONS))
                return;

            size_t tickrate = 1;

            const auto &animationsSettings = config.lookup(CFG_ANIMATIONS);
            if (animationsSettings.exists("tickrate"))
                tickrate = parseNumber<size_t>(animationsSettings, "tickrate");

            scene->setKeyframesTick(tickrate);
            if (!animationsSettings.exists("keyframes"))
                return;
            for (const auto &keyframe : animationsSettings.lookup("keyframes"))
                parseKeyframe(keyframe, scene);
        }
    } // namespace Parsing
} // namespace Raytracer
