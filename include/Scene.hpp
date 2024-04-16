/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Scene.h
*/

#pragma once

#include <list>
#include <memory>

#include "IPrimitive.hpp"

namespace Raytracer {
    class Scene {
        public:
            Scene() = default;
            ~Scene() = default;

            void addPrimitive(std::unique_ptr<IPrimitive> obj);

        private:
            std::list<std::unique_ptr<IPrimitive>> m_list;
    };
}
