/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Ray.hpp
*/

#pragma once

#include "APrimitive.hpp"
#include "Triangle.hpp"
#include <vector>


namespace Raytracer {
    class Obj : public APrimitive {
    public:
        Obj(const std::string &obj_path, std::unique_ptr<IMaterial> material,
            const Math::Vector3D &position = Math::Vector3D(0, 0, 0),
            Math::Vector3D scale = Math::Vector3D(1, 1, 1));
        ~Obj() = default;

        PrimitiveType getType(void) const override { return PrimitiveType::OBJ; };

        std::string getTexturePath() const;
        const std::string &getObjPath(void) const { return m_objPath; };
        Math::Vector3D getScale(void) const { return m_scale; };
        std::vector<std::unique_ptr<Triangle>> &getTriangles(void) { return m_triangles; };

        void setIsShown(bool isShown) override;
        void setOrigin(const Math::Vector3D &v) override;
        void setMaterial(std::unique_ptr<IMaterial> material) override;
        void setScale(const Math::Vector3D &scale);

        void applyMaterialToTriangles(void);

        BoundingBox getBoundingBox(void) const override { return BoundingBox(Math::Vector3D(0, 0, 0), Math::Vector3D(0, 0, 0)); };
        std::optional<RayHit> hit(const Ray &ray) const override { (void)ray; return std::nullopt; };

    private:
        std::string m_objPath;

        Math::Vector3D m_scale;

        std::vector<std::unique_ptr<Triangle>> m_triangles;
    };
} // namespace Raytracer

