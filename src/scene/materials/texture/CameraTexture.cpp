/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** CameraTexture.cpp
*/

#include "Scene/Materials/MaterialTexture/CameraTexture.hpp"

#include <cmath>

namespace Raytracer {
    Color CameraTexture::getColor(const RayHit &ray) const
    {
        // #ifdef BONUSCAMERA
        // #endif
        this->SphereTexture::getColor(ray);
        // return SphereTexture::getColor(ray);
    }

    // #ifdef BONUSCAMERA
    // void CameraTexture::setCamera(RealCamera &camera)
    // {
    //     m_camera = camera;
    //     setImage(m_camera->getCurrentFrame());
    // }
    // #endif
} // namespace Raytracer
