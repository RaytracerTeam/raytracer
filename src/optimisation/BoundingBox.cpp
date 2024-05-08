/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** BoundingBox.cpp
*/

#include "Optimisation/BoundingBox.hpp"

namespace Raytracer {
    bool BoundingBox::intersect(const Ray &ray) const
    {
        double tmin = (min.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();
        double tmax = (max.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();

        if (tmin > tmax)
            std::swap(tmin, tmax);

        double tymin = (min.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();
        double tymax = (max.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();

        if (tymin > tymax)
            std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
            tmin = tymin;
        if (tymax < tmax)
            tmax = tymax;

        double tzmin = (min.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();
        double tzmax = (max.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();

        if (tzmin > tzmax)
            std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        return true;
    }

    double BoundingBox::surfaceArea(void) const
    {
        Math::Vector3D offset = max - min;

        return offset.getX() * offset.getY()
            + offset.getY() * offset.getZ()
            + offset.getZ() * offset.getX();
    }

    Math::Vector3D BoundingBox::closestPointOnPerimeter(const Ray &ray) const
    {
        // Calculate the closest point on each edge of the bounding box to the ray's origin
        Math::Vector3D points[8]; // 8 points for the corners of the box

        // Calculate all 8 corners of the box
        points[0] = min;
        points[1] = Math::Vector3D(max.getX(), min.getY(), min.getZ());
        points[2] = Math::Vector3D(min.getX(), max.getY(), min.getZ());
        points[3] = Math::Vector3D(max.getX(), max.getY(), min.getZ());
        points[4] = Math::Vector3D(min.getX(), min.getY(), max.getZ());
        points[5] = Math::Vector3D(max.getX(), min.getY(), max.getZ());
        points[6] = Math::Vector3D(min.getX(), max.getY(), max.getZ());
        points[7] = max;

        // Find the closest point among these 8 points to the ray's origin
        double minDistance = std::numeric_limits<double>::max();
        Math::Vector3D closestPoint;
        for (const auto &point : points) {
            Math::Vector3D rayToPoint = point - ray.getOrigin();
            double distance = rayToPoint.length();
            if (distance < minDistance) {
                minDistance = distance;
                closestPoint = point;
            }
        }

        return closestPoint;
    }
} // namespace Raytracer
