/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseOptimization
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer {
    namespace Parsing {
        void parseOptimization(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_OPTIMIZATION))
                return;
            const libconfig::Setting &setting = config.lookup(CFG_OPTIMIZATION);
            if (setting.exists(CFG_MAX_RAY_BOUNCES)) {
                scene->setMaxRayBounces((int)setting.lookup(CFG_MAX_RAY_BOUNCES));
            }
            if (setting.exists(CFG_BVH_MAX_PRIM)) {
                scene->setBvhMaxPrimLimit((int)setting.lookup(CFG_BVH_MAX_PRIM));
            }
            if (setting.exists(CFG_USE_MULTITHREADING)) {
                bool useMultithreading = setting.lookup(CFG_USE_MULTITHREADING);
                if (!useMultithreading)
                    scene->setNbThreads(1);
            }
        }
    } // namespace Parsing
} // namespace Raytracer
