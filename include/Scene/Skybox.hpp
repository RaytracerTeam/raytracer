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
        void setTexure(std::unique_ptr<MaterialTexture> material) { m_texture = std::move(material); };
        void setSolidColor(const Color &color) { m_solidColor = color; }
        void setHasTexture(bool hasTexture) { m_hasTexture = hasTexture; }

        MaterialTexture *getMaterialTexture(void) const { return m_texture.get(); }
        MaterialTexture *getTexture(void) const { return m_texture.get(); }
        Color getSolidColor(void) const { return m_solidColor; }
        bool hasTexture(void) const { return m_hasTexture; }

        SkyboxUVType getSkyboxUVTypee(void) const { return m_uvtype; }
        void setSkyboxUVTypee(SkyboxUVType type);

        Color getAmbientColor(const Ray &ray) const;
        Color getAmbientColor(void) const;
    private:
        Color getAmbientColorUVSphere(const Ray &ray) const;
        Color getAmbientColorBox(const Ray &ray) const;
        Color (Skybox::*m_methodAmbientColor)(const Ray &) const = nullptr;
        std::unique_ptr<MaterialTexture> m_texture;
        bool m_hasTexture = false;
        Color m_solidColor = Color(0U, 0, 0);
        SkyboxUVType m_uvtype;
    };
} // namespace Raytracer
