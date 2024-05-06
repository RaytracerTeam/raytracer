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
} // namespace Raytracer
