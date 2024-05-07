/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BVH.cpp
*/

#include "Optimisation/BVH.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

namespace Raytracer {
    namespace BVH {

        static Axis getBiggestAxis(const BoundingBox &box)
        {
            if (box.max.getX() < box.max.getY())
                return box.max.getY() < box.max.getZ() ? Z : Y;
            else
                return box.max.getX() < box.max.getZ() ? Z : X;
        }

        static double getBiggestAxisVal(const BoundingBox &box)
        {
            if (box.max.getX() < box.max.getY())
                return std::max(box.max.getY(), box.max.getZ());
            else
                return std::max(box.max.getX(), box.max.getZ());
        }

        static auto getBiggestAxisMethod(Axis axis)
        {
            switch (axis) {
            case X:
                return &Math::Vector3D::getX;
            case Y:
                return &Math::Vector3D::getY;
            default:
                return &Math::Vector3D::getZ;
            }
        }

        static BoundingBox getBoundBox(std::vector<const IPrimitive *> &primitives)
        {
            Math::Vector3D overallMin(INFINITY, INFINITY, INFINITY);
            Math::Vector3D overallMax(-INFINITY, -INFINITY, -INFINITY);

            std::for_each(primitives.begin(), primitives.end(), [&](const IPrimitive *primitive) {
                const BoundingBox &boundingBox = primitive->getBoundingBox();

                overallMin = {
                    std::min(overallMin.getX(), boundingBox.min.getX()),
                    std::min(overallMin.getY(), boundingBox.min.getY()),
                    std::min(overallMin.getZ(), boundingBox.min.getZ())
                };

                overallMax = {
                    std::max(overallMax.getX(), boundingBox.max.getX()),
                    std::max(overallMax.getY(), boundingBox.max.getY()),
                    std::max(overallMax.getZ(), boundingBox.max.getZ())
                };
            });
            return { overallMin, overallMax };
        }

        static std::pair<std::vector<const IPrimitive *>, std::vector<const IPrimitive *>> getSubdivision(double sepThreshold,
            double (Math::Vector3D::*getAxis)(void) const, std::vector<const IPrimitive *> &primitives)
        {
            auto pair = std::pair<std::vector<const IPrimitive *>, std::vector<const IPrimitive *>>();

            auto partitionMedian = std::partition(primitives.begin(), primitives.end(),
                [getAxis, sepThreshold](const IPrimitive *prim) {
                    return (prim->getOrigin().*getAxis)() < sepThreshold;
                });

            std::copy(primitives.begin(), partitionMedian, std::back_inserter(pair.first));
            std::copy(partitionMedian, primitives.end(), std::back_inserter(pair.second));
            return pair;
        }

        // nPrims should never be zero.
        std::unique_ptr<Node> createBVH(size_t nPrims,
            std::vector<const IPrimitive *> &primitives,
            double (*seperateFunc)(double (Math::Vector3D::*biggestAxisM)() const, std::vector<const IPrimitive *> &primitives))
        {
            auto node = std::make_unique<Node>(getBoundBox(primitives));

            if (primitives.size() > nPrims) {
                Axis biggestAxis = getBiggestAxis(node->box);
                auto biggestAxisM = getBiggestAxisMethod(biggestAxis);
                double sepThreshold = seperateFunc(biggestAxisM, primitives);
                auto res = getSubdivision(sepThreshold, biggestAxisM, primitives);
                if (res.first.size() == primitives.size() || res.second.size() == primitives.size()) {
                    // give up, can't seperated them, todo : maybe add another algorithms
                    node->primitives = std::make_unique<std::vector<const IPrimitive *>>(primitives);
                    return node;
                }
                node->left = createBVH(nPrims, res.first, seperateFunc);
                node->right = createBVH(nPrims, res.second, seperateFunc);
                return node;
            }
            node->primitives = std::make_unique<std::vector<const IPrimitive *>>(primitives);
            return node;
        }

        std::optional<std::pair<RayHit, const IPrimitive *>> readBVH(const Ray &ray, const Node &node)
        {
            if (!node.box.intersect(ray))
                return std::nullopt;

            if (node.primitives == nullptr) {
                auto resLeft = readBVH(ray, *node.left);
                if (resLeft != std::nullopt)
                    return resLeft;
                return readBVH(ray, *node.right);
            }

            std::vector<std::pair<RayHit, const IPrimitive *>> hitResults;
            auto vec = *node.primitives;
            for (const auto &prim : vec) {
                if (!prim->isShown())
                    continue;
                auto hitResult = prim->hit(ray);
                if (hitResult != std::nullopt)
                    hitResults.push_back(std::pair<RayHit, const IPrimitive *>(*hitResult, prim));
            }

            if (hitResults.size() == 0)
                return std::nullopt;
            std::sort(
                begin(hitResults),
                end(hitResults),
                [](const std::pair<RayHit, const IPrimitive *> &lhs, const std::pair<RayHit, const IPrimitive *> &rhs) {
                    return lhs.first.getDistance() < rhs.first.getDistance();
                });
            return hitResults.front();
        }
    }
}
