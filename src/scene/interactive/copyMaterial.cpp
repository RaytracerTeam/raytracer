/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** copyMaterial
*/

#include "Scene/Interactive/SceneInteractive.hpp"
#include "Scene/Materials/AllMaterials.hpp"

namespace Raytracer
{
    std::unique_ptr<IMaterial> SceneInteractive::copyMaterial(IMaterial *material)
    {
        switch (material->getType()) {
        case MaterialType::SOLID:
            return std::make_unique<MaterialSolid>(*static_cast<MaterialSolid *>(material));
        case MaterialType::CHECKERBOARD:
            return std::make_unique<MaterialCheckerBoard>(*static_cast<MaterialCheckerBoard *>(material));
        case MaterialType::TEXTURE_CUBE:
            return std::make_unique<CubeTexture>(*static_cast<CubeTexture *>(material));
        case MaterialType::TEXTURE_SPHERE:
            return std::make_unique<SphereTexture>(*static_cast<SphereTexture *>(material));
        case MaterialType::TEXTURE_PLANE:
            return std::make_unique<PlaneTexture>(*static_cast<PlaneTexture *>(material));
        case MaterialType::TEXTURE_TRIANGLE:
            return std::make_unique<TriangleTexture>(*static_cast<TriangleTexture *>(material));
        default:
            return std::make_unique<MaterialSolid>(Color(1., 0, 1));
        }
    }
} // namespace Raytracer
