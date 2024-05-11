/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** CameraTexture
*/

#pragma once

#include "Scene/Materials/MaterialTexture/SphereTexture.hpp"
#ifdef BONUSCAMERA
    #include "RealCamera.hpp"
#endif

namespace Raytracer {
    class CameraTexture : public SphereTexture {
    public:
        ~CameraTexture() = default;

        MaterialType getType() const override { return MaterialType::CAMERA; }

        // #ifdef BONUSCAMERA
        //     void setCamera(RealCamera &camera);
        // #endif

        Color getColor(const RayHit &rayhit) const override;
    private:
        // #ifdef BONUSCAMERA
        //     RealCamera &m_camera;
        // #endif
    };
} // namespace Raytracer
