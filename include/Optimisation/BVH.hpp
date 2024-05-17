/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BVH.hpp
*/

#pragma once

#include "Scene/Interfaces/IPrimitive.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace Raytracer {

    /**
     * @brief Bounding Volume Hierarchy namespace
     */
    namespace BVH {
        /**
         * @brief Axis enum for the BVH in 3d space
         */
        enum Axis {
            X,
            Y,
            Z
        };

        /**
         * @brief Bounding Box class
         */
        class Node {
        public:
            /**
             * @brief Constructor of the Node class
             * @param b The bounding box
             **/
            Node(const BoundingBox &b)
                : box(b)
            {
            }
            ~Node() = default;

            BoundingBox box; ///< The bounding box
            std::unique_ptr<std::vector<const IPrimitive *>> primitives; ///< The primitives
            std::unique_ptr<Node> left; ///< The left node
            std::unique_ptr<Node> right; ///< The right node
        };

        /**
         * @brief Intersection class
         */
        class Intersection {
            public:
                RayHit rayhit; ///< The ray hit
                const IPrimitive *primitve; ///< The primitive
        };

        /**
         * @brief createBVH function around the primitives
         * 
         * @param nPrims 
         * @param primitives 
         * @param seperateFunc 
         * @return return a new node
         */
        std::unique_ptr<Node> createBVH(size_t nPrims,
            std::vector<const IPrimitive *> &primitives,
            double (*seperateFunc)(double (Math::Vector3D::*biggestAxisM)() const,
            std::vector<const IPrimitive *> &primitives));
        
        /**
         * @brief readBVH function and apply the ray to the node and the primitives
         * 
         * @param ray 
         * @param node 
         * @param intersection 
         * @return true if the ray hit the node 
         */
        bool readBVH(const Ray &ray, const Node &node, Intersection &intersection);

        // Algorithms

        /**
         * @brief subdivision of a BVH 
         * 
         * @param biggestAxisM 
         * @param primitives 
         * @return where to cut the BVH
         */
        double axisAligned(double (Math::Vector3D::*biggestAxisM)() const, std::vector<const IPrimitive *> &primitives);
        double surfaceAreaHeuristic(double (Math::Vector3D::*biggestAxisM)() const, std::vector<const IPrimitive *> &primitives);

    } // namespace BVH
} // namespace Raytracer
