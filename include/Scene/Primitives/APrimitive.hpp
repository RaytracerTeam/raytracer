/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.h
*/

#pragma once

#include "Scene/Interfaces/IPrimitive.hpp"

namespace Raytracer {
    class APrimitive : public IPrimitive {
    public:
        void setOrigin(const Math::Vector3D &v) override
        {
            m_origin = v;
        }
        void setTMatrix(const Math::Matrix44 &mat) override
        {
            m_mat = mat;
        }
        void setTMatrix(double rotX, double rotY, double rotZ) override
        {
            m_mat = Math::Matrix44(rotX, rotY, rotZ);
        }

        void setMaterial(std::unique_ptr<IMaterial> material) override
        {
            m_material = std::move(material);
        }
        void setIsShown(bool isShown) override { m_isShown = isShown; }

        const Math::Vector3D &getOrigin(void) const override final { return m_origin; }
        const Math::Matrix44 &getTMatrix(void) const override final { return m_mat; }
        std::unique_ptr<IMaterial> &getMaterial(void) override final { return m_material; };
        const std::unique_ptr<IMaterial> &getMaterial(void) const override { return m_material; };
        PrimitiveType getType(void) const override { return PrimitiveType::NONE; };
        const std::string getTypeString(void) const override { return PrimitiveTypeStrings[static_cast<int>(getType())]; };
        int getID(void) const override { return m_id; }
        void setID(int id) override { m_id = id; }
        void dieASAP(void) override { m_dieASAP = true; }
        bool getDieASAP(void) const override { return m_dieASAP; }
        void setDieASAP(bool dieASAP) override { m_dieASAP = dieASAP; }
        void setRotXYZ(double rotX, double rotY, double rotZ) override
        {
            m_mat = Math::Matrix44(rotX, rotY, rotZ);
        }
        bool isShown(void) const override { return m_isShown; }
    protected:
        APrimitive(const Math::Vector3D &origin,  std::unique_ptr<IMaterial> material)
            : m_origin(origin)
            , m_material(std::move(material)) {};
        ~APrimitive() = default;

        int m_id = -1;
        Math::Vector3D m_origin;
        Math::Matrix44 m_mat;
        std::unique_ptr<IMaterial> m_material;
        bool m_isShown = true;
        bool m_dieASAP = false;
    };
} // namespace Raytracer
