/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** IObject.hpp
*/

#pragma once

namespace Raytracer {
    class IObject {
    public:
        virtual ~IObject() = default;

        virtual void setIsShown(bool isShown) = 0;
        virtual void setDieASAP(bool dieASAP) = 0;
        virtual bool isShown(void) const = 0;
        virtual bool getDieASAP(void) const = 0;
        virtual void dieASAP(void) = 0;
    };
} // namespace Raytracer
