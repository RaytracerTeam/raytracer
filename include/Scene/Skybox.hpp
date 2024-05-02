/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Skybox.hpp
*/

#pragma once

#include "Color.hpp"
#include "Ray.hpp"

#include "Materials/MaterialTexture.hpp"

namespace Raytracer {
    enum SkyboxUVType {
        SPHERE,
        BOX
    };

    class Skybox {
    public:
        Skybox(std::unique_ptr<MaterialTexture> texture, SkyboxUVType type = SPHERE);
        Skybox() = default;
        ~Skybox() = default;

        void setMaterialTexture(std::unique_ptr<MaterialTexture> material) { m_texture = std::move(material); };
        MaterialTexture *getMaterialTexture(void) const { return m_texture.get(); }
        void setTexure(std::unique_ptr<MaterialTexture> material) { m_texture = std::move(material); };
        MaterialTexture *getTexture(void) const { return m_texture.get(); }

        SkyboxUVType getSkyboxUVTypee(void) const { return m_uvtype; }
        void setSkyboxUVTypee(SkyboxUVType type);

        Color getAmbientColor(const Ray &ray) const;
    private:
        Color getAmbientColorUVSphere(const Ray &ray) const;
        Color getAmbientColorBox(const Ray &ray) const;
        Color (Skybox::*m_methodAmbientColor)(const Ray &) const = nullptr;
        std::unique_ptr<MaterialTexture> m_texture;
        SkyboxUVType m_uvtype;
    };
} // namespace Raytracer
