/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BoundingBox.hpp
*/

#pragma once

#include "Math/Vector3D.hpp"
#include "Scene/Ray.hpp"

namespace Raytracer {
    class BoundingBox {
    public:

        /**
         * @brief Constructor of the BoundingBox class
         * @param min_ The minimum value of the bounding box
         * @param max_ The maximum value of the bounding box
         **/
        BoundingBox(const Math::Vector3D &min_, const Math::Vector3D &max_)
            : min(min_)
            , max(max_)
        {
        }
        ~BoundingBox() = default;

        /**
         * @brief Checks if a ray intersects with the bounding box
         * @param ray The ray to check
         * @return True if the ray intersects, false otherwise
         **/
        bool intersect(const Ray &ray) const;

        /**
         * @brief Get the surface area of the bounding box
         * @return The surface area of the bounding box
         **/
        double surfaceArea(void) const;

        /**
         * @brief Get the closest point on the perimeter of the bounding box
         * @param ray The ray to check
         * @return The closest point on the perimeter of the bounding box
         **/
        Math::Vector3D closestPointOnPerimeter(const Ray &ray) const;

        Math::Vector3D min; ///< The minimum value of the bounding box
        Math::Vector3D max; ///< The maximum value of the bounding box
    };
} // namespace Raytracer
