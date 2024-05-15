/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MatrixT
*/

#include "Math/MatrixT.hpp"
#include <cmath>

namespace Raytracer {
    namespace Math {
        MatrixT::MatrixT(const Matrix44 &fwdTransform, const Matrix44 &bwkTransform)
            : m_fwdTransform(fwdTransform)
            , m_bwkTransform(bwkTransform)
        {
        }

        void MatrixT::setTransform(const Vector3D &translation, const Vector3D &rotation, const Vector3D &scale)
        {
            Matrix44 translationMatrix;
            Matrix44 rotateXMatrix;
            Matrix44 rotateYMatrix;
            Matrix44 rotateZMatrix;
            Matrix44 scaleMatrix;

            translationMatrix[0][3] = translation.getX();
            translationMatrix[1][3] = translation.getY();
            translationMatrix[2][3] = translation.getZ();

            rotateXMatrix[1][1] = cos(rotation.getX());
            rotateXMatrix[1][2] = -sin(rotation.getX());
            rotateXMatrix[2][1] = sin(rotation.getX());
            rotateXMatrix[2][2] = cos(rotation.getX());

            rotateYMatrix[0][0] = cos(rotation.getY());
            rotateYMatrix[0][2] = sin(rotation.getY());
            rotateYMatrix[2][0] = -sin(rotation.getY());
            rotateYMatrix[2][2] = cos(rotation.getY());

            rotateZMatrix[0][0] = cos(rotation.getZ());
            rotateZMatrix[0][1] = -sin(rotation.getZ());
            rotateZMatrix[1][0] = sin(rotation.getZ());
            rotateZMatrix[1][1] = cos(rotation.getZ());

            scaleMatrix[0][0] = scale.getX();
            scaleMatrix[1][1] = scale.getY();
            scaleMatrix[2][2] = scale.getZ();

            m_fwdTransform = translationMatrix * scaleMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;
            m_bwkTransform = m_fwdTransform.inverse();
        }

        void MatrixT::setTransform(const Transformations &transformations)
        {
            setTransform(transformations.getTranslation(), transformations.getRotation(), transformations.getScale());
        }

        Ray MatrixT::applyForward(const Ray &ray) const
        {
            return Ray(applyForward(ray.getOrigin()), applyForward(ray.getDirection()));
        }

        Ray MatrixT::applyBackward(const Ray &ray) const
        {
            return Ray(applyBackward(ray.getOrigin()), applyBackward(ray.getDirection()));
        }

        Vector3D MatrixT::applyForward(const Vector3D &vec) const
        {
            std::array<double, 4> src = { vec.getX(), vec.getY(), vec.getZ(), 1 };
            return m_fwdTransform * src;
        }

        Vector3D MatrixT::applyBackward(const Vector3D &vec) const
        {
            std::array<double, 4> src = { vec.getX(), vec.getY(), vec.getZ(), 1 };
            return m_bwkTransform * src;
        }
    }
}
