/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseObj
*/

#include "Parsing/Parsing.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Raytracer {
    namespace Parsing {
        void readObj(const std::string &path, std::unique_ptr<Scene> &scene,
            const Math::Vector3D &translation, const Math::Vector3D &scale,
            std::unique_ptr<IMaterial> material)
        {
            std::ifstream file(path);
            if (!file.is_open()) {
                std::cerr << "Error: Unable to open file " << path << std::endl;
                return;
            }

            std::vector<Math::Vector3D> vertices;
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
                } else if (token == "f") {
                    std::string i1, i2, i3;
                    iss >> i1 >> i2 >> i3;
                    int index1, index2, index3;
                    index1 = std::stoi(i1.substr(0, i1.find('/')));
                    index2 = std::stoi(i2.substr(0, i2.find('/')));
                    index3 = std::stoi(i3.substr(0, i3.find('/')));
                    Math::Vector3D origin = vertices[index1 - 1];
                    Math::Vector3D v1 = vertices[index2 - 1];
                    Math::Vector3D v2 = vertices[index3 - 1];
                    scene->addPrimitive(std::make_unique<Triangle>(
                        origin,
                        std::make_unique<MaterialSolid>(static_cast<MaterialSolid &>(*material)),
                        v1, v2));
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
                        parseMaterial(objSetting));
                }
            }
        }
    } // namespace Parsing
} // namespace Raytracer
