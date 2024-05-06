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
        void readObj(const std::string &path, std::unique_ptr<Scene> &scene)
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
                    vertices.push_back(vertex);
                } else if (token == "f") {
                    int index1, index2, index3;
                    iss >> index1 >> index2 >> index3;
                    Math::Vector3D origin = vertices[index1 - 1];
                    Math::Vector3D v1 = vertices[index2 - 1];
                    Math::Vector3D v2 = vertices[index3 - 1];
                    scene->addPrimitive(std::make_unique<Triangle>(
                        origin,
                        std::make_unique<MaterialSolid>(Color(255U, 255, 255)),
                        v1, v2));
                }
            }
            file.close();
        }
        void parseObj(const libconfig::Config &config, std::unique_ptr<Scene> &scene)
        {
            if (!config.exists(CFG_OBJ))
                return;

            for (const auto &objSetting : config.lookup(CFG_OBJ)) {
                if (objSetting.exists(CFG_PATH)) {
                    readObj(objSetting.lookup(CFG_PATH), scene);
                }
            }
        }
    } // namespace Parsing
} // namespace Raytracer
