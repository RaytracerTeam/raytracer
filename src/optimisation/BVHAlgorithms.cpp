/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BVHAlgorithms.cpp
*/

#include "Optimisation/BVH.hpp"

#include <algorithm>

namespace Raytracer {
    namespace BVH {
        // median based axis
        double axisAligned(double (Math::Vector3D::*getAxis)(void) const, std::vector<const IPrimitive *> &primitives)
        {
            std::sort(
                begin(primitives),
                end(primitives),
                [getAxis](const IPrimitive *lhs, const IPrimitive *rhs) {
                    return (lhs->getOrigin().*getAxis)() < (rhs->getOrigin().*getAxis)();
                });
            if (primitives.size() % 2 == 1)
                return (primitives.at(primitives.size() / 2)->getOrigin().*getAxis)();
            auto prim1Og = (primitives.at(primitives.size() / 2 - 1)->getOrigin().*getAxis)();
            auto prim2Og = (primitives.at(primitives.size() / 2)->getOrigin().*getAxis)();
            return 0.5 * (prim1Og + prim2Og);
        }

        double surfaceAreaHeuristic(double (Math::Vector3D::*getAxis)(void) const, std::vector<const IPrimitive *> &primitives)
        {
            (void)getAxis;
            (void)primitives;
            return 0.;
        }
    }
}
