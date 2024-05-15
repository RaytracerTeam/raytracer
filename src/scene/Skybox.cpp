/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Skybox.cpp
*/

#include "Scene/Skybox.hpp"

#include <cmath>

namespace Raytracer {
    Skybox::Skybox(std::unique_ptr<MaterialTexture> texture, SkyboxUVType type)
        : m_texture(std::move(texture))
        , m_uvtype(type)
    {
        setSkyboxUVTypee(m_uvtype);
    }

    void Skybox::setSkyboxUVTypee(SkyboxUVType type)
    {
        m_uvtype = type;
        switch (type) {
        case SPHERE:
            m_methodAmbientColor = &Skybox::getAmbientColorUVSphere;
            break;
        case BOX:
            m_methodAmbientColor = &Skybox::getAmbientColorBox;
            break;
        default:
            throw Error("Unknown skybox UV type", "Skybox::setSkyboxUVTypee");
        }
    }

    Color Skybox::getAmbientColor(void) const
    {
        return m_solidColor;
    }

    Color Skybox::getAmbientColor(const Ray &ray) const
    {
        if (!m_hasTexture || m_texture.get() == nullptr || m_methodAmbientColor == nullptr)
            return m_solidColor;

        return (*this.*m_methodAmbientColor)(ray);
    }

    Color Skybox::getAmbientColorUVSphere(const Ray &ray) const
    {
        if (m_texture.get() == nullptr || m_methodAmbientColor == nullptr)
            return Color(1., 0, 1);

        auto d = ray.getDirection();
        float u = (0.5 + std::atan2(d.getZ(), d.getX()) / (2 * M_PI));
        float v = (0.5 - std::asin(d.getY()) / M_PI);
        return m_texture->getColor(u, v);
    }

    Color Skybox::getAmbientColorBox(const Ray &ray) const
    {
        auto origin = ray.getDirection();
        double lon = std::atan2(origin.getY(), origin.getX());
        double lat = std::atan2(
            origin.getZ(),
            std::sqrt(
                std::pow(origin.getX(), 2.) + std::pow(origin.getY(), 2.)));

        double u = (lon + M_PI) / (2. * M_PI);
        double v = (std::log(std::tan(lat / 2. + M_PI / 4.)) + M_PI)
            / (2. * M_PI);
        return m_texture->getColor(u, v);
    }
} // namespace Raytracer
