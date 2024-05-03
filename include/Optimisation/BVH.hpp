/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BVH.hpp
*/

#pragma once

#include "Scene/Interfaces/IPrimitive.hpp"

#include <memory>
#include <vector>
#include <optional>

namespace Raytracer {
    namespace BVH {
        enum Axis {
            X,
            Y,
            Z
        };

        class Node {
        public:
            Node(const BoundingBox &b) : box(b) {}
            ~Node() = default;

            BoundingBox box;
            std::unique_ptr<std::vector<const IPrimitive *>> primitives;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
        };

        std::unique_ptr<Node> createBVH(size_t nPrims,
            std::vector<const IPrimitive *> &primitives,
            double (*seperateFunc)(double (Math::Vector3D::*biggestAxisM)() const, std::vector<const IPrimitive *> &primitives));
        std::optional<std::pair<RayHit, const IPrimitive *>> readBVH(const Ray &ray, const Node &node);

        // Algorithms

        double axisAligned(double (Math::Vector3D::*biggestAxisM)() const, std::vector<const IPrimitive *> &primitives);
        double surfaceAreaHeuristic(double (Math::Vector3D::*biggestAxisM)() const, std::vector<const IPrimitive *> &primitives);

    } // namespace BVH
} // namespace Raytracer
