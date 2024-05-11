/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Cube.cpp
*/

#include "Scene/Primitives/Cube.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Algorithm.hpp"

namespace Raytracer {
    BoundingBox Cube::getBoundingBox(void) const
    {
        Math::Vector3D min = Math::Vector3D(
            std::min(m_origin.getX(), m_v1.getX()) - getTMatrix().getScaling()[0],
            std::min(m_origin.getY(), m_v1.getY()) - getTMatrix().getScaling()[1],
            std::min(m_origin.getZ(), m_v1.getZ()) - getTMatrix().getScaling()[2]);
        Math::Vector3D max = Math::Vector3D(
            std::max(m_origin.getX(), m_v1.getX()) + getTMatrix().getScaling()[0],
            std::max(m_origin.getY(), m_v1.getY()) + getTMatrix().getScaling()[1],
            std::max(m_origin.getZ(), m_v1.getZ()) + getTMatrix().getScaling()[2]);
        return BoundingBox(min, max);
    }

    RayHit Cube::getNormal(double distance, const Math::Vector3D &hitPt, int hitFace) const
    {
        Math::Vector3D normal;

        switch (hitFace) {
		case 0:
            normal = Math::Vector3D(-1, 0, 0);
            break;
		case 1:
            normal = Math::Vector3D(0, -1, 0);
            break;
		case 2:
            normal = Math::Vector3D(0, 0, -1);
            break;
		case 3:
            normal = Math::Vector3D(1, 0, 0);
            break;
		case 4:
            normal = Math::Vector3D(0, 1, 0);
            break;
		case 5:
            normal = Math::Vector3D(0, 0, 1);
            break;
        }

        return RayHit(distance, hitPt, normal);
	}

    std::optional<RayHit> Cube::hit(const Ray &ray) const
    {
        Math::Vector3D dstOrigin = getTMatrix() * ray.getOrigin();
        Math::Vector3D rayDir = getTMatrix() * ray.getDirection();

        BoundingBox box = getBoundingBox();
        Math::Vector3D v0 = box.min;
        Math::Vector3D v1 = box.max;

        Math::Vector3D tMin;
        Math::Vector3D tMax;

        double a = 1. / rayDir.getX();

        if (a > TOLERANCE) {
            tMin.setX((v0.getX() - dstOrigin.getX()) * a);
            tMax.setX((v1.getX() - dstOrigin.getX()) * a);
        } else {
            tMin.setX((v1.getX() - dstOrigin.getX()) * a);
            tMax.setX((v0.getX() - dstOrigin.getX()) * a);
        }

        double b = 1. / rayDir.getY();

        if (b > TOLERANCE) {
            tMin.setY((v0.getY() - dstOrigin.getY()) * b);
            tMax.setY((v1.getY() - dstOrigin.getY()) * b);
        } else {
            tMin.setY((v1.getY() - dstOrigin.getY()) * b);
            tMax.setY((v0.getY() - dstOrigin.getY()) * b);
        }

        double c = 1. / rayDir.getZ();

        if (c > TOLERANCE) {
            tMin.setZ((v0.getZ() - dstOrigin.getZ()) * c);
            tMax.setZ((v1.getZ() - dstOrigin.getZ()) * c);
        } else {
            tMin.setZ((v1.getZ() - dstOrigin.getZ()) * c);
            tMax.setZ((v0.getZ() - dstOrigin.getZ()) * c);
        }

        double t0;
        double t1;
        int faceIn;
        int faceOut;

        if (tMin.getX() > tMin.getY()) {
            t0 = tMin.getX();
            faceIn = (a > TOLERANCE) ? 0 : 3;
        } else {
            t0 = tMin.getY();
            faceIn = (b > TOLERANCE) ? 1 : 4;
        }
        if (tMin.getZ() > t0) {
            t0 = tMin.getZ();
            faceIn = (c > TOLERANCE) ? 2 : 5;
        }

        if (tMax.getX() < tMax.getY()) {
            t1 = tMax.getX();
            faceOut = (a > TOLERANCE) ? 3 : 0;
        } else {
            t1 = tMax.getY();
            faceOut = (b > TOLERANCE) ? 4 : 1;
        }
        if (tMax.getZ() < t1) {
            t1 = tMax.getZ();
            faceOut = (c > TOLERANCE) ? 5 : 2;
        }

        if (!(t0 < t1 && t1 > TOLERANCE))
            return std::nullopt;

        if (t0 > TOLERANCE) {
            Math::Vector3D hit = ray.getOrigin() + ray.getDirection() * t0;
            return getNormal(t0, hit, faceIn);
        } else {
            Math::Vector3D hit = ray.getOrigin() + ray.getDirection() * t1;
            return getNormal(t1, hit, faceOut);
        }

        return std::nullopt;
    }
} // namespace Raytracer
