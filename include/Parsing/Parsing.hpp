/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Parsing.hpp
*/

#pragma once

#include <string>
#include <filesystem>
#include <libconfig.h++>
#include "Scene/Scene.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Primitives/Plane.hpp"
#include "Scene/Primitives/Cylinder.hpp"
#include "Scene/Primitives/Cone.hpp"

namespace Raytracer {
    namespace Parsing {
        bool parseArgv(int argc, char **argv, std::vector<std::string_view> &inputFiles); // return true if interactive mode
        void parse(Scene &scene, const std::vector<std::string_view> &inputFiles);

        Math::Vector3D parsePosition(const libconfig::Setting &setting);
        Math::Angle3D parseRotation(const libconfig::Setting &setting);
        MaterialSolid parseColor(const libconfig::Setting &setting);
        float parseHeight(const libconfig::Setting &setting);
        float parseRadius(const libconfig::Setting &setting);

        void parsePrimitives(const libconfig::Config &config, Scene &scene);
        void parseSpheres(const libconfig::Setting &primitiveSetting, Scene &scene);
        void parsePlanes(const libconfig::Setting &primitiveSetting, Scene &scene);
        void parseCylinders(const libconfig::Setting &primitiveSetting, Scene &scene);
        void parseCones(const libconfig::Setting &primitiveSetting, Scene &scene);
        // void parseToruses(const libconfig::Setting &primitiveSetting, Scene &scene);
        // void parseTriangles(const libconfig::Setting &primitiveSetting, Scene &scene);


        void parseCameras(const libconfig::Config &config, Scene &scene);
        void parseLights(const libconfig::Config &config, Scene &scene);

        void saveScene(const Scene &scene, const std::string &outputFile);
        void saveCameras(const Scene &scene, libconfig::Setting &root);
        void saveLights(const Scene &scene, libconfig::Setting &root);
        void savePrimitives(const Scene &scene, libconfig::Setting &root);
        void saveSphere(const Scene &scene, libconfig::Setting &sphereList, Sphere *sphere);
        void saveCylinder(const Scene &scene, libconfig::Setting &list, Cylinder *cylinder);
        // void saveCone(const Scene &scene, libconfig::Setting &list, Cone *cone);
        // void saveTorus(const Scene &scene, libconfig::Setting &list, Torus *torus);
        // void saveTriangle(const Scene &scene, libconfig::Setting &list, Triangle *triangle);
        void savePlane(const Scene &scene, libconfig::Setting &planeList, Plane *plane);

        Math::Vector3D getSettingPosition(const libconfig::Setting &setting);
        Math::Angle3D getSettingRotation(const libconfig::Setting &setting);
        Color getSettingColor(const libconfig::Setting &setting);
    } // namespace Parsing
} // namespace Raytracing
