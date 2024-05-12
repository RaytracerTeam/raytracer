/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseObj
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialTexture/TriangleTexture.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Raytracer {
    namespace Parsing {
        void readObj(const std::string &path, std::unique_ptr<Scene> &scene,
            const Math::Vector3D &translation, const Math::Vector3D &scale,
            std::unique_ptr<IMaterial> material, std::string texturePath = "")
        {
            std::ifstream file(path);
            if (!file.is_open()) {
                std::cerr << "Error: Unable to open file " << path << std::endl;
                return;
            }

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
                    vertices.push_back(vertex * scale + translation);
                } else if (token == "vt") {
                    double x, y;
                    iss >> x >> y;
                    Math::Vector3D vertexTexture(x, y, 0);
                    vertexTextures.push_back(vertexTexture);
                } else if (token == "f") {
                    std::string i1, i2, i3;
                    iss >> i1 >> i2 >> i3;

                    // Vertices
                    int vertexIndex1, vertexIndex2, vertexIndex3;
                    vertexIndex1 = std::stoi(i1.substr(0, i1.find('/')));
                    vertexIndex2 = std::stoi(i2.substr(0, i2.find('/')));
                    vertexIndex3 = std::stoi(i3.substr(0, i3.find('/')));
                    Math::Vector3D origin = vertices[vertexIndex1 - 1];
                    Math::Vector3D v1 = vertices[vertexIndex2 - 1];
                    Math::Vector3D v2 = vertices[vertexIndex3 - 1];


                    // Vertex textures
                    if (vertexTextures.size() > 0 && !texturePath.empty()) {
                        std::shared_ptr<sf::Image> image = std::make_shared<sf::Image>();
                        if (!image->loadFromFile(texturePath)) {
                            std::cerr << "Error: No texture path provided or incorrect" << std::endl;
                            continue;
                        }
                        int vertexTextureIndex1, vertexTextureIndex2, vertexTextureIndex3;
                        vertexTextureIndex1 = std::stoi(i1.substr(i1.find('/') + 1, i1.find_last_of('/')));
                        vertexTextureIndex2 = std::stoi(i2.substr(i2.find('/') + 1, i2.find_last_of('/')));
                        vertexTextureIndex3 = std::stoi(i3.substr(i3.find('/') + 1, i3.find_last_of('/')));
                        Math::Vector3D vt1 = vertexTextures[vertexTextureIndex1 - 1];
                        Math::Vector3D vt2 = vertexTextures[vertexTextureIndex2 - 1];
                        Math::Vector3D vt3 = vertexTextures[vertexTextureIndex3 - 1];
                        scene->addPrimitive(std::make_unique<Triangle>(
                            origin,
                            std::make_unique<TriangleTexture>(image, vt3, vt2, vt1),
                            v1, v2, true));
                    } else {
                        scene->addPrimitive(std::make_unique<Triangle>(
                            origin,
                            std::make_unique<MaterialSolid>(static_cast<MaterialSolid &>(*material)),
                            v1, v2, true));
                    }
                }
            }
            file.close();
        }
        void parseObj(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_OBJ))
                return;

            Math::Vector3D translation = Math::Vector3D(0, 0, 0);
            Math::Vector3D scale = Math::Vector3D(1, 1, 1);

            for (const auto &objSetting : config.lookup(CFG_OBJ)) {
                translation = parsePosition(objSetting);
                auto &transformationSetting = objSetting.lookup(CFG_TRANSFORMATIONS);
                scale = parseVec3D(transformationSetting, CFG_SCALE, Math::Vector3D(1, 1, 1));
                if (objSetting.exists(CFG_PATH)) {
                    readObj(objSetting.lookup(CFG_PATH), scene, translation, scale,
                        parseMaterial(objSetting, PrimitiveType::TRIANGLE),
                        objSetting.exists(CFG_MATERIAL_TEXTURE) ? objSetting.lookup(CFG_MATERIAL_TEXTURE) : "");
                }
            }
        }
    } // namespace Parsing
} // namespace Raytracer
