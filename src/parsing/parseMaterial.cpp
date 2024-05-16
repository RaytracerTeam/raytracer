/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseMaterial
*/

#include "Parsing/Parsing.hpp"
#include "Scene/Materials/AllMaterials.hpp"

namespace Raytracer {
    namespace Parsing {
        static std::unique_ptr<MaterialTexture> parseMaterialTexture(const libconfig::Setting &setting, PrimitiveType primType)
        {
            // if (!setting.exists(CFG_PATH))
            //     return std::make_unique<MaterialTexture>("");
            switch (primType) {
            case PrimitiveType::SPHERE:
                return std::make_unique<SphereTexture>(setting.lookup(CFG_PATH));
            case PrimitiveType::TRIANGLE: {
                if (!setting.exists(CFG_PATH))
                    return std::make_unique<TriangleTexture>();
                return std::make_unique<TriangleTexture>(setting.lookup(CFG_PATH));
            }
            case PrimitiveType::PLANE:
                return std::make_unique<PlaneTexture>(setting.lookup(CFG_PATH));
            case PrimitiveType::CUBE:
                return std::make_unique<CubeTexture>(setting.lookup(CFG_PATH));
            default:
                return std::make_unique<MaterialTexture>(setting.lookup(CFG_PATH));
            }
        }

        static std::unique_ptr<MaterialTexture> parseMaterialCamera(PrimitiveType primType)
        {
            switch (primType) {
            case PrimitiveType::SPHERE:
                return std::make_unique<SphereTexture>();
            case PrimitiveType::TRIANGLE:
                return std::make_unique<TriangleTexture>();
            case PrimitiveType::PLANE:
                return std::make_unique<PlaneTexture>();
            case PrimitiveType::CUBE:
                return std::make_unique<CubeTexture>();
            default:
                break;
            }
            return nullptr;
        }

        std::unique_ptr<IMaterial> parseMaterial(const libconfig::Setting &setting,
        PrimitiveType primType) {
            if (!setting.exists(CFG_MATERIAL))
                return std::make_unique<MaterialSolid>(Color(1., 0, 1));
            libconfig::Setting &materialSetting = setting.lookup("material");
            if (!materialSetting.exists(CFG_TYPE))
                return std::make_unique<MaterialSolid>(Color(1., 0, 1));

            std::unique_ptr<IMaterial> material;
            std::string materialType = materialSetting.lookup(CFG_TYPE);
            if (materialType == CFG_MATERIAL_SOLID_COLOR) {
                material = std::make_unique<MaterialSolid>(getSettingColor(materialSetting));
            }
            else if (materialType == CFG_MATERIAL_TEXTURE) {
                material = parseMaterialTexture(materialSetting, primType);
            }
            else if (materialType == CFG_MATERIAL_CHECKERBOARD && materialSetting.exists("color_bis")) {
                material = std::make_unique<MaterialCheckerBoard>(
                    getSettingColor(materialSetting),
                    getSettingColor(materialSetting.lookup("color_bis")),
                    parseNumber<float>(materialSetting, CFG_SIZE, 1.0));
            }
            else if (materialType == CFG_CAMERA) {
                material = parseMaterialCamera(primType);
                #ifdef BONUSCAMERA
                material->setIsCamera(true);
                #endif
            }
            else {
                return std::make_unique<MaterialSolid>(Color(1., 0, 1));
            }

            if (materialSetting.exists(CFG_DIFFUSE))
                material->setDiffuse(parseNumber<float>(materialSetting, CFG_DIFFUSE, 0.0));
            if (materialSetting.exists(CFG_SPECULAR))
                material->setSpecular(parseNumber<float>(materialSetting, CFG_SPECULAR, 0.0));
            if (materialSetting.exists(CFG_SHININESS))
                material->setShininess(parseNumber<float>(materialSetting, CFG_SHININESS, 0.0));

            if (materialSetting.exists(CFG_REFLECTION))
                material->setReflection(parseNumber<float>(materialSetting, CFG_REFLECTION, 0.0));

            if (materialSetting.exists(CFG_TRANSPARENCY))
                material->setTransparency(parseNumber<float>(materialSetting, CFG_TRANSPARENCY, 0.0));
            if (materialSetting.exists(CFG_REFRACTION))
                material->setRefraction(parseNumber<float>(materialSetting, CFG_REFRACTION, 1.3));

            return material;
        }
    } // namespace Parsing
} // namespace Raytracer
