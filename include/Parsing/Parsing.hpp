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
#include "Writer.hpp"

namespace Raytracer {
    namespace Parsing {
        #define CONFIG_DIR "config"
        #define KEYS_CONFIG CONFIG_DIR"/keys.cfg"
        #define KEYS_CONFIG_EXAMPLE CONFIG_DIR"/keys_example.cfg"

        #define CFG_GLOBAL "global"
        #define CFG_SKYBOX "skybox"
        #define CFG_PATH "path"
        #define CFG_HASTEXTURE "hasTexture"
        // Lights
        #define CFG_AMBIENT_LIGHT "ambientLight"
        #define CFG_INTENSITY "intensity"
        // Camera
        #define CFG_CAMERA "camera"
        #define CFG_ANIMATIONS "animations"
        #define CFG_OBJ "objs"
        #define CFG_FOV "fov"
        #define CFG_RESOLUTION "resolution"
        // Primitives
        #define CFG_POSITION "position"
        #define CFG_ROTATION "rotation"
        #define CFG_HEIGHT "height"
        #define CFG_SCALE "scale"
        #define CFG_TRANSLATION "translation"
        #define CFG_COLOR "color"
        #define CFG_RADIUS "radius"
        #define CFG_DISTANCE "distance"
        #define CFG_TRANSPARENCY "transparency"
        #define CFG_REFRACTION "refraction"
        #define CFG_POINT_LIGHTS "pointLights"
        #define CFG_DIRECTIONAL_LIGHTS "directionalLights"
        #define CFG_DIRECTION "direction"
        #define CFG_TRANSFORMATIONS "transformations"
        // Optimization
        #define CFG_OPTIMIZATION "optimization"
        #define CFG_MAX_RAY_BOUNCES "maxRayBounces"
        #define CFG_BVH_MAX_PRIM "maxPrimitivesPerBvhBox"
        #define CFG_USE_MULTITHREADING "useMultithreading"

        #define CFG_V0 "v0"
        #define CFG_V1 "v1"
        #define CFG_V2 "v2"
        // Material
        #define CFG_MATERIAL_TYPE "materialType"
        #define CFG_MATERIAL "material"
        #define CFG_TYPE "type"
        #define CFG_MATERIAL_SOLID_COLOR "solid_color"
        #define CFG_MATERIAL_TEXTURE "texture"
        #define CFG_MATERIAL_CHECKERBOARD "checkerboard"
        #define CFG_COLOR_BIS "color_bis"
        #define CFG_SIZE "size"
        #define CFG_DIFFUSE "diffuse"
        #define CFG_SPECULAR "specular"
        #define CFG_SHININESS "shininess"
        #define CFG_REFLECTION "reflection"
        // Interactive
        #define CFG_INTERACTIVE "interactive"
        #define CFG_SPEED "speed"
        #define CFG_SENSITIVITY "sensitivity"
        #define CFG_ALWAYS_RENDER "alwaysRender"
        #define CFG_CAMERA_SPEED "speed"
        #define CFG_CAMERA_SENSITIVITY "sensitivity"
        // Inventory
        #define CFG_INVENTORY "inventory"
        // Primitives
        #define CFG_SPHERES "spheres"
        #define CFG_PLANES "planes"
        #define CFG_TRIANGLES "triangles"
        #define CFG_CYLINDERS "cylinders"
        #define CFG_CONES "cones"
        #define CFG_CUBES "cubes"
        #define CFG_TORUSES "toruses"
        #define CFG_TANGLECUBES "tanglecubes"

        class ParsingResult {
            public:
                bool interactiveMode;
                bool animationMode;
                std::string path;
        };

        WriteFile::WriteType parseFormat(const std::string_view &format);
        ParsingResult parseArgv(int argc, char **argv,
            std::vector<std::string_view> &inputFiles, WriteFile::WriteType &type); // return true if interactive mode
        void parse(std::unique_ptr<Scene> &scene, const std::string_view &file);
        void parse(std::unique_ptr<Scene> &scene, const std::vector<std::string_view> &file);

        template <typename T>
        T parseNumber(const libconfig::Setting &setting, const std::string &key, T defaultValue = 0)
        {
            if (setting.exists(key.c_str())) {
                if (setting.lookup(key.c_str()).getType() == libconfig::Setting::TypeInt)
                    return (T)((int)setting.lookup(key.c_str()));
                return setting.lookup(key.c_str());
            }
            return defaultValue;
        }


        Math::Vector3D parsePosition(const libconfig::Setting &setting);
        Math::Angle3D parseRotation(const libconfig::Setting &setting);
        MaterialSolid parseMaterialColor(const libconfig::Setting &setting);
        float parseHeight(const libconfig::Setting &setting);
        float parseRadius(const libconfig::Setting &setting);
        float parseDistance(const libconfig::Setting &setting);
        Math::Vector3D parseVec3D(const libconfig::Setting &setting, const std::string &key,
            Math::Vector3D defaultValue = Math::Vector3D(0, 0, 0));
        float parseIntensity(const libconfig::Setting &setting);
        std::unique_ptr<IMaterial> parseMaterial(const libconfig::Setting &setting,
            MaterialType materialTextureType = MaterialType::NONE);
        Transformations parseTransformations(const libconfig::Setting &setting);

        void parsePrimitives(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseSpheres(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parsePlanes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseCylinders(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseCones(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseToruses(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseTanglecubes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseTriangles(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
        void parseCubes(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);

        void parseGlobal(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseOptimization(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseCameras(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseLights(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseAnimations(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseObjs(const libconfig::Config &config, std::unique_ptr<Scene> &scene);
        void parseInventory(const libconfig::Config &config, std::unique_ptr<Scene> &scene);

        void saveVector3D(libconfig::Setting &setting, const std::string &key, const Math::Vector3D vec);
        void savePos(libconfig::Setting &setting, const Math::Vector3D pos);
        void saveColor(libconfig::Setting &setting, const Color color);
        void saveMaterial(libconfig::Setting &setting, const std::unique_ptr<Raytracer::IMaterial> &material);
        void saveTransformations(libconfig::Setting &setting, APrimitive *primitive);

        void saveScene(const Scene &scene, const std::string &outputFile);
        void saveGlobal(const Scene &scene, libconfig::Setting &root);
        void saveOptimization(const Scene &scene, libconfig::Setting &root);
        void saveCameras(const Scene &scene, libconfig::Setting &root);
        void saveLights(const Scene &scene, libconfig::Setting &root);
        void saveObjs(const Scene &scene, libconfig::Setting &root);
        void saveInventory(const Scene &scene, libconfig::Setting &root);
        void savePrimitives(const Scene &scene, libconfig::Setting &root);
        void saveSphere(libconfig::Setting &list, Sphere *sphere);
        void saveCylinder(libconfig::Setting &list, Cylinder *cylinder);
        void saveCone(libconfig::Setting &list, Cone *cone);
        void saveTorus(libconfig::Setting &list, Torus *torus);
        void saveTanglecube(libconfig::Setting &list, Tanglecube *tanglecube);
        void saveTriangle(libconfig::Setting &list, Triangle *triangle);
        void savePlane(libconfig::Setting &list, Plane *plane);
        void saveCube(libconfig::Setting &list, Cube *cube);

        Math::Angle3D getSettingRotation(const libconfig::Setting &setting);
        Color getSettingColor(const libconfig::Setting &setting);
    } // namespace Parsing
} // namespace Raytracing
