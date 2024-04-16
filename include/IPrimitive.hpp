/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IPrimitive.h
*/

#pragma once

#include "Math/Vector3.hpp"

namespace Raytracer {
    class IPrimitive {
        public:
            virtual void setPosition(Math::Vector3 &v) = 0;
    };
}
