/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveOptimization
*/

#include "Parsing/Parsing.hpp"

namespace Raytracer
{
    void Parsing::saveOptimization(const Scene &scene, libconfig::Setting &root)
    {
        libconfig::Setting &setting = root.add(CFG_OPTIMIZATION, libconfig::Setting::TypeGroup);
        setting.add(CFG_MAX_RAY_BOUNCES, libconfig::Setting::TypeInt) = (int)scene.getMaxRayBounces();
        setting.add(CFG_USE_MULTITHREADING, libconfig::Setting::TypeBoolean) = scene.getNbThreads() > 1;
    }
} // namespace Raytracer

