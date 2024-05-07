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
#include "Scene/Primitives/AllPrimitives.hpp"

namespace Raytracer {
    namespace Parsing {
        #define KEYS_CONFIG "config/keys.cfg"
        #define KEYS_CONFIG_EXAMPLE "config/keys_example.cfg"

        #define CFG_GLOBAL "global"
        #define CFG_SKYBOX "skybox"
        #define CFG_PATH "path"
        #define CFG_HASTEXTURE "hasTexture"

        #define CFG_AMBIENT_LIGHT "ambientLight"
        #define CFG_OBJ "obj"
        #define CFG_FOV "fov"
        #define CFG_RESOLUTION "resolution"
        #define CFG_POSITION "position"
        #define CFG_ROTATION "rotation"
        #define CFG_SCALE "scale"
        #define CRG_TRANSLATION "translation"
        #define CFG_COLOR "color"
        #define CFG_RADIUS "radius"
        #define CFG_HEIGHT "height"
        #define CFG_WIDTH "width"
        #define CFG_DISTANCE "distance"
        #define CFG_INTENSITY "intensity"
        #define CFG_ALBEDO "albedo"
        #define CFG_FUZZ "fuzz"
        #define CFG_EMISSION "emission"
        #define CFG_HAS_PHONG "hasPhong"

        #define CFG_V0 "v0"
        #define CFG_V1 "v1"
        #define CFG_V2 "v2"

        #define CFG_MATERIAL "material"
        #define CFG_TYPE "type"
        #define CFG_MATERIAL_SOLID_COLOR "solid_color"

        bool parseArgv(int argc, char **argv, std::vector<std::string_view> &inputFiles); // return true if interactive mode
        void parse(std::unique_ptr<Scene> &scene, const std::vector<std::string_view> &inputFiles);

        float parseFloat(const libconfig::Setting &setting, const std::string &key, float defaultValue);
        Math::Vector3D parsePosition(const libconfig::Setting &setting);
        Math::Angle3D parseRotation(const libconfig::Setting &setting);
        MaterialSolid parseColor(const libconfig::Setting &setting);
        float parseHeight(const libconfig::Setting &setting);
        float parseRadius(const libconfig::Setting &setting);
        float parseDistance(const libconfig::Setting &setting);
        Math::Vector3D parseVec3D(const libconfig::Setting &setting, const std::string &key,
            Math::Vector3D defaultValue = Math::Vector3D(0, 0, 0));
        float parseIntensity(const libconfig::Setting &setting);
        std::unique_ptr<MaterialSolid> parseMaterialSolid(const libconfig::Setting &setting);

        void parsePrimitives(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseSpheres(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parsePlanes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseCylinders(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseCones(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseToruses(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseTanglecubes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseTriangles(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);

        void parseGlobal(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseCameras(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseLights(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseObj(const libconfig::Config &config, std::unique_ptr<Scene> &scene);

        void savePos(libconfig::Setting &setting, ISceneObj *obj);
        void saveColor(libconfig::Setting &setting, Color color);
        void saveMaterialSolid(libconfig::Setting &setting, APrimitive *primitive);

        void saveScene(const Scene &scene, const std::string &outputFile);
        void saveGlobal(const Scene &scene, libconfig::Setting &root);
        void saveObj(const Scene &scene, libconfig::Setting &root);
        void saveCameras(const Scene &scene, libconfig::Setting &root);
        void saveLights(const Scene &scene, libconfig::Setting &root);
        void savePrimitives(const Scene &scene, libconfig::Setting &root);
        void saveSphere(libconfig::Setting &list, Sphere *sphere);
        void saveCylinder(libconfig::Setting &list, Cylinder *cylinder);
        void saveCone(libconfig::Setting &list, Cone *cone);
        void saveTorus(libconfig::Setting &list, Torus *torus);
        void saveTanglecube(libconfig::Setting &list, Tanglecube *tanglecube);
        void saveTriangle(libconfig::Setting &list, Triangle *triangle);
        void savePlane(libconfig::Setting &list, Plane *plane);

        Math::Angle3D getSettingRotation(const libconfig::Setting &setting);
        Color getSettingColor(const libconfig::Setting &setting);
    } // namespace Parsing
} // namespace Raytracing
