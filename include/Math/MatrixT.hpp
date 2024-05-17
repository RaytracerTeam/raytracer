/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** MatrixT
*/

#pragma once

#include "Matrix44d.hpp"
#include "Scene/Ray.hpp"
#include "Scene/Transformations.hpp"

namespace Raytracer {
    namespace Math {
        class MatrixT {
        public:
            MatrixT() = default;
            ~MatrixT() = default;

            MatrixT(const Matrix44 &fwdTransform, const Matrix44 &bwkTransform);

            void setTransform(const Vector3D &translation, const Vector3D &rotation, const Vector3D &scale);
            void setTransform(const Transformations &transformations);

            Ray applyForward(const Ray &ray) const;
            Ray applyBackward(const Ray &ray) const;

            Vector3D applyForward(const Vector3D &vec) const;
            Vector3D applyBackward(const Vector3D &vec) const;

        private:
            Matrix44 m_fwdTransform;
            Matrix44 m_bwkTransform;
        };
    }
}
