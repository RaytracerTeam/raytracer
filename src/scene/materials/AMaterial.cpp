/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** AMaterial.cpp
*/

#include "Scene/Materials/AMaterial.hpp"
#include "Math/Algorithm.hpp"

namespace Raytracer {
    /*
    calculates specular composant
    Admits we have clear view of light
    https://euler.ac-versailles.fr/IMG/pdf/raytracing.pdf
    */
    Color AMaterial::getSpecular(const ILight *light, const RayHit &rayhit, const Math::Vector3D &lightVec) const
    {
        Math::Vector3D n = rayhit.getNormal();
        const Math::Vector3D &l = lightVec;
        if (l.dot(n) <= 0.001)
            return Color();

        Math::Vector3D r = (n * 2. * (n.dot(l))) - l;
        return light->getColor() * (std::pow(l.dot(r), 30));
    }

    // todo : add fuzzing that makes reflections go random direction
    std::optional<Ray> AMaterial::getScatteredRay(const Ray &rayIn, const RayHit &rayHit) const
    {
        Math::Vector3D reflected = Math::Vector3D::gReflect(rayIn.getDirection().normalize(), rayHit.getNormal());
        Ray rayScattered = Ray(rayHit.getHitPoint(), reflected, rayIn.getDepth() + 1);

        if (rayScattered.getDirection().dot(rayHit.getNormal()) <= 0.001)
            return std::nullopt;
        return rayScattered;
    }

    std::optional<Ray> AMaterial::getTransparencyReflectionRay(const Ray &rayIn, const RayHit &rayHit) const
    {
        Math::Vector3D normal = rayHit.getNormal();
        float cosi = Math::Algorithm::clampD(rayIn.getDirection().dot(rayHit.getNormal()), -1., 1.);
        float etai = 1;
        float etat = 1.3;

        if (cosi < 0) {
            cosi = -cosi;
        } else {
            std::swap(etai, etat);
            normal = -rayHit.getNormal();
        }

        float eta = etai / etat;
        float k = 1 - eta * eta * (1 - cosi * cosi);
        if (k < 0)
            return std::nullopt;

        Math::Vector3D refracted = rayIn.getDirection() * eta + normal * (eta * cosi - sqrtf(k));
        Ray rayTransparency = Ray(rayHit.getHitPoint(), refracted, rayIn.getDepth() + 1);

        return rayTransparency;
    }

    std::optional<Ray> AMaterial::getTransparencyRay(const Ray &rayIn, const RayHit &rayHit) const
    {
        Ray rayTransparency = Ray(rayHit.getHitPoint(), rayIn.getDirection(), rayIn.getDepth() + 1);
        return rayTransparency;
    }
} // namespace Raytracer
