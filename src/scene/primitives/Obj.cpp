/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Obj.cpp
*/

#include "Scene/Primitives/Obj.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <memory>
#include <SFML/Graphics.hpp>
#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Materials/MaterialTexture/TriangleTexture.hpp"

namespace Raytracer {
    Obj::Obj(const Math::Vector3D &origin, std::unique_ptr<IMaterial> material,
        Transformations transformations, const std::string &objPath)
        : APrimitive(origin, std::move(material), transformations)
        , m_objPath(objPath)
    {
        try {
        std::ifstream file(objPath);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << objPath << std::endl;
            return;
        }

        const std::string texturePath = getTexturePath();

        std::vector<Math::Vector3D> vertices;
        std::vector<Math::Vector3D> vertexTextures;
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;
            if (token == "v") {
                double x, y, z;
                iss >> x >> y >> z;
                Math::Vector3D vertex(x, y, z);
                vertices.push_back(vertex * m_transformations.getScale() + m_origin + m_transformations.getTranslation());
            } else if (token == "vt") {
                double x, y;
                iss >> x >> y;
                Math::Vector3D vertexTexture(x, y, 0);
                vertexTextures.push_back(vertexTexture);
            } else if (token == "f") {
                std::string i1, i2, i3, i4;
                iss >> i1 >> i2 >> i3 >> i4;
                bool isQuad = !i4.empty();

                // Vertices
                int vertexIndex1, vertexIndex2, vertexIndex3, vertexIndex4;
                vertexIndex1 = std::stoi(i1.substr(0, i1.find('/')));
                vertexIndex2 = std::stoi(i2.substr(0, i2.find('/')));
                vertexIndex3 = std::stoi(i3.substr(0, i3.find('/')));
                Math::Vector3D origin = vertices[vertexIndex1 - 1];
                Math::Vector3D v1 = vertices[vertexIndex2 - 1];
                Math::Vector3D v2 = vertices[vertexIndex3 - 1];
                Math::Vector3D v3;

                if (isQuad) {
                    vertexIndex4 = std::stoi(i4.substr(0, i4.find('/')));
                    v3 = vertices[vertexIndex4 - 1];
                }

                // Vertex textures
                if (vertexTextures.size() > 0 && !texturePath.empty()) {
                    std::shared_ptr<sf::Image> image = std::make_shared<sf::Image>();
                    if (!image->loadFromFile(texturePath)) {
                        std::cerr << "Error: No texture path provided or incorrect" << std::endl;
                        continue;
                    }
                    int vertexTextureIndex1, vertexTextureIndex2, vertexTextureIndex3, vertexTextureIndex4;
                    vertexTextureIndex1 = std::stoi(i1.substr(i1.find('/') + 1, i1.find_last_of('/')));
                    vertexTextureIndex2 = std::stoi(i2.substr(i2.find('/') + 1, i2.find_last_of('/')));
                    vertexTextureIndex3 = std::stoi(i3.substr(i3.find('/') + 1, i3.find_last_of('/')));
                    Math::Vector3D vt1 = vertexTextures[vertexTextureIndex1 - 1];
                    Math::Vector3D vt2 = vertexTextures[vertexTextureIndex2 - 1];
                    Math::Vector3D vt3 = vertexTextures[vertexTextureIndex3 - 1];
                    Math::Vector3D vt4;
                    if (isQuad) {
                        vertexTextureIndex4 = std::stoi(i4.substr(i4.find('/') + 1, i4.find_last_of('/')));
                        vt4 = vertexTextures[vertexTextureIndex4 - 1];
                    }
                    m_triangles.push_back(std::make_unique<Triangle>(
                        origin,
                        std::make_unique<TriangleTexture>(image, vt2, vt3, vt1),
                        Transformations(), v1, v2, true));
                    if (isQuad) {
                        m_triangles.push_back(std::make_unique<Triangle>(
                            v2,
                            std::make_unique<TriangleTexture>(image, vt1, vt4, vt3),
                            Transformations(), origin, v3, true));
                    }
                } else {
                    m_triangles.push_back(std::make_unique<Triangle>(
                        origin,
                        std::make_unique<MaterialSolid>(static_cast<MaterialSolid &>(*m_material)),
                        Transformations(), v1, v2, true));
                    if (isQuad) {
                        m_triangles.push_back(std::make_unique<Triangle>(
                            v2,
                            std::make_unique<MaterialSolid>(static_cast<MaterialSolid &>(*m_material)),
                            Transformations(), v3, origin, true));
                    }
                }
            }
        }
        file.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    std::string Obj::getTexturePath() const
    {
        if (m_material->getType() == MaterialType::TEXTURE_TRIANGLE) {
            return static_cast<TriangleTexture *>(m_material.get())->getPathname();
        }
        return std::string("");
    }

    void Obj::setIsShown(bool isShown)
    {
        m_isShown = isShown;
        for (auto &triangle : m_triangles)
            triangle->setIsShown(isShown);
    }

    void Obj::setOrigin(const Math::Vector3D &v)
    {
        Math::Vector3D diff = v - m_origin;
        for (auto &triangle : m_triangles) {
            triangle->setOrigin(triangle->getOrigin() + diff);
            triangle->setVec1(triangle->getVec1() + diff);
            triangle->setVec2(triangle->getVec2() + diff);
        }
        m_origin = v;
    }

    void Obj::setTranslation(const Math::Vector3D &translation)
    {
        Math::Vector3D diff = translation - m_transformations.getTranslation();
        for (auto &triangle : m_triangles) {
            triangle->setOrigin(triangle->getOrigin() + diff);
            triangle->setVec1(triangle->getVec1() + diff);
            triangle->setVec2(triangle->getVec2() + diff);
        }
        m_transformations.setTranslation(translation);
    }

    void Obj::setRotation(const Math::Vector3D &rotation)
    {
        for (auto &triangle : m_triangles)
            triangle->setRotation(rotation);
        m_transformations.setRotation(rotation);
    }

    void Obj::setScale(const Math::Vector3D &scale)
    {
        for (auto &triangle : m_triangles) {
            triangle->setOrigin(triangle->getOrigin() / m_transformations.getScale() * scale);
            triangle->setVec1(triangle->getVec1() / m_transformations.getScale() * scale);
            triangle->setVec2(triangle->getVec2() / m_transformations.getScale() * scale);
        }
        m_transformations.setScale(scale);
    }

    void Obj::setMaterial(std::unique_ptr<IMaterial> material)
    {
        m_material = std::move(material);
        applyMaterialToTriangles();
    }

    void Obj::applyMaterialToTriangles(void)
    {
        for (auto &triangle : m_triangles) {
            switch (m_material->getType()) {
            case MaterialType::SOLID:
                triangle->setMaterial(std::make_unique<MaterialSolid>(
                    static_cast<MaterialSolid &>(*m_material)));
                break;
            case MaterialType::TEXTURE_TRIANGLE:
                triangle->setMaterial(std::make_unique<TriangleTexture>(
                    static_cast<TriangleTexture &>(*m_material)));
                break;
            default:
                break;
            }
        }
    }
} // namespace Raytracer
