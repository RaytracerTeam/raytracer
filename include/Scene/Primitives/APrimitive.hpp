/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** APrimitive.h
*/

#pragma once

#include "Scene/Interfaces/IPrimitive.hpp"
#include "Scene/Transformations.hpp"

namespace Raytracer {
    class APrimitive : public IPrimitive {
    public:
        void setOrigin(const Math::Vector3D &v) override
        {
            m_origin = v;
            updateTransformations();
        }
        void setMaterial(std::unique_ptr<IMaterial> material) override
        {
            m_material = std::move(material);
        }
        void setIsShown(bool isShown) override
        {
            m_isShown = isShown;
        }

        void setTranslation(const Math::Vector3D &translation) override
        {
            m_transformations.setTranslation(translation);
            m_matrixT.setTransform(m_transformations);
            updateTransformations();
        }
        void setRotation(const Math::Vector3D &rotation) override
        {
            m_transformations.setRotation(rotation);
            m_matrixT.setTransform(m_transformations);
            updateTransformations();
        }
        void setScale(const Math::Vector3D &scale) override
        {
            m_transformations.setScale(scale);
            m_matrixT.setTransform(m_transformations);
            updateTransformations();
        }

        const Math::Vector3D &getOrigin(void) const override final { return m_origin; }

        const Math::MatrixT &getMatrixT(void) const override final { return m_matrixT; }
        const Math::Vector3D &getTranslation(void) const override final { return m_transformations.getTranslation(); }
        const Math::Vector3D &getRotation(void) const override final { return m_transformations.getRotation(); }
        const Math::Vector3D &getScale(void) const override final { return m_transformations.getScale(); }

        std::unique_ptr<IMaterial> &getMaterial(void) override final { return m_material; };
        const std::unique_ptr<IMaterial> &getMaterial(void) const override { return m_material; };

        PrimitiveType getType(void) const override { return PrimitiveType::NONE; };
        const std::string getTypeString(void) const override { return PrimitiveTypeStrings[static_cast<int>(getType())]; };

        int getID(void) const override { return m_id; }
        void setID(int id) override { m_id = id; }
        void dieASAP(void) override { m_dieASAP = true; }
        bool getDieASAP(void) const override { return m_dieASAP; }
        void setDieASAP(bool dieASAP) override { m_dieASAP = dieASAP; }
        bool isShown(void) const override { return m_isShown; }

        void updateTransformations(void) override final
        {
            m_bckOrigin = m_matrixT.applyBackward(m_origin);
            m_fwdOrigin = m_matrixT.applyForward(m_bckOrigin);
            m_bckTranslation = m_matrixT.applyBackward(m_transformations.getTranslation());
            m_fwdTranslation = m_matrixT.applyForward(m_bckTranslation);
        }

    protected:
        APrimitive(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material,
            const Transformations &transformations)
            : m_origin(origin)
            , m_material(std::move(material))
            , m_transformations(transformations)
        {
            m_matrixT.setTransform(transformations);
            updateTransformations();
        }
        ~APrimitive() = default;

        int m_id = -1;
        Math::Vector3D m_origin;
        Math::Vector3D m_bckOrigin;
        Math::Vector3D m_fwdOrigin;
        std::unique_ptr<IMaterial> m_material;
        Transformations m_transformations;
        Math::Vector3D m_bckTranslation;
        Math::Vector3D m_fwdTranslation;
        Math::MatrixT m_matrixT;
        bool m_isShown = true;
        bool m_dieASAP = false;
    };
} // namespace Raytracer
