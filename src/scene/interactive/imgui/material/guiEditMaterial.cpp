/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** guiEditMaterial
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Materials/AllMaterials.hpp"

namespace Raytracer
{
    bool SceneInteractive::customEditMaterial(std::unique_ptr<IMaterial> &material)
    {
        bool materialChanged = false;
        switch (material->getType()) {
        case MaterialType::SOLID: {
            ImGui::SameLine(0, 20);
            // Color
            ImGui::SetNextItemWidth(200);
            MaterialSolid *materialSolid = static_cast<MaterialSolid *>(material.get());
            float *color = materialSolid->getColor();
            if (ImGui::ColorEdit3("Color", color)) {
                materialSolid->setColor(color);
                materialChanged = true;
            }
            break;
        }
        case MaterialType::CHECKERBOARD: {
            MaterialCheckerBoard *checkerBoard = static_cast<MaterialCheckerBoard *>(material.get());
            // Color
            ImGui::SetNextItemWidth(200);
            float *color = checkerBoard->getC1();
            if (ImGui::ColorEdit3("Color", color)) {
                checkerBoard->setC1(color);
                materialChanged = true;
            }
            ImGui::SameLine(0, 20);
            // Color bis
            ImGui::SetNextItemWidth(200);
            float *colorBis = checkerBoard->getC2();
            if (ImGui::ColorEdit3("Color bis", colorBis)) {
                checkerBoard->setC2(colorBis);
                materialChanged = true;
            }
            ImGui::SameLine(0, 20);
            // Size
            ImGui::SetNextItemWidth(200);
            float size = checkerBoard->getFactor();
            if (ImGui::SliderFloat("Size", &size, 0.01f, 1000.0f, "%.2f",
            ImGuiSliderFlags_Logarithmic)) {
                checkerBoard->setFactor(size);
                materialChanged = true;
            }
            break;
        }
        case MaterialType::TEXTURE_TRIANGLE: {
            TriangleTexture *triangleTexture = static_cast<TriangleTexture *>(material.get());
            // VT1
            float *vt1 = triangleTexture->getVT1();
            if (ImGui::SliderFloat3("VT1", vt1, 0, 1, "%.2f",
            ImGuiSliderFlags_AlwaysClamp)) {
                triangleTexture->setVT1(vt1);
                materialChanged = true;
            }
            // VT2
            float *vt2 = triangleTexture->getVT2();
            if (ImGui::SliderFloat3("VT2", vt2, 0, 1, "%.2f",
            ImGuiSliderFlags_AlwaysClamp)) {
                triangleTexture->setVT2(vt2);
                materialChanged = true;
            }
            // VT3
            float *vt3 = triangleTexture->getVT3();
            if (ImGui::SliderFloat3("VT3", vt3, 0, 1, "%.2f",
            ImGuiSliderFlags_AlwaysClamp)) {
                triangleTexture->setVT3(vt3);
                materialChanged = true;
            }
            break;
        }
        case MaterialType::TEXTURE_PLANE: {
            PlaneTexture *planeTexture = static_cast<PlaneTexture *>(material.get());
            // Size
            float size = planeTexture->getFactor();
            if (ImGui::SliderFloat("Size", &size, 0.01f, 1000.0f, "%.2f",
            ImGuiSliderFlags_Logarithmic)) {
                planeTexture->setFactor(size);
                materialChanged = true;
            }
            break;
        }
        default:
            break;
        }
        return materialChanged;
    }

    bool SceneInteractive::changeMaterialType(std::unique_ptr<IMaterial> &material)
    {
        bool materialChanged = false;
        ImGui::SetNextItemWidth(200);
        if (ImGui::BeginCombo("Type", material->getTypeString().c_str())) {
            for (const auto &entry : MaterialTypeStrings) {
                if (ImGui::Selectable(entry)) {
                    if (strcmp(entry, "Solid") == 0) {
                        material = std::make_unique<MaterialSolid>(Color(1., 1, 1));
                    } else if (strcmp(entry, "Checkerboard") == 0) {
                        material = std::make_unique<MaterialCheckerBoard>();
                    } else if (strcmp(entry, "TextureTriangle") == 0) {
                        material = std::make_unique<TriangleTexture>();
                    } else if (strcmp(entry, "TexturePlane") == 0) {
                        material = std::make_unique<PlaneTexture>();
                    } else if (strcmp(entry, "TextureSphere") == 0) {
                        material = std::make_unique<SphereTexture>();
                    } else if (strcmp(entry, "TextureCube") == 0) {
                        material = std::make_unique<CubeTexture>();
                    }
                    #ifdef BONUSCAMERA
                    material->setIsCamera(false);
                    #endif
                    materialChanged = true;
                }
            }
            ImGui::EndCombo();
        }
        switch (material->getType()) {
        case MaterialType::TEXTURE:
        case MaterialType::TEXTURE_PLANE:
        case MaterialType::TEXTURE_SPHERE:
        case MaterialType::TEXTURE_TRIANGLE:
        case MaterialType::TEXTURE_CUBE: {
            if (!std::filesystem::exists(TEXTURE_PATH)) {
                break;
            }
            ImGui::SameLine(0, 20);
            ImGui::SetNextItemWidth(300);
            MaterialTexture *materialTexture = static_cast<MaterialTexture *>(material.get());
            if (ImGui::BeginCombo("Texture Path", materialTexture->getPathname().c_str())) {
                for (const auto &path : TEXTURE_PATHS) {
                    if (!std::filesystem::exists(path))
                        continue;
                    for (const auto &entry : std::filesystem::directory_iterator(path)) {
                        if (ImGui::Selectable(entry.path().filename().string().c_str())) {
                            materialTexture->setTexture(entry.path().string());
                            #ifdef BONUSCAMERA
                            materialTexture->setIsCamera(false);
                            #endif
                            materialChanged = true;
                        }
                    }
                }
                #ifdef BONUSCAMERA
                if (ImGui::Selectable("Camera")) {
                    materialTexture->setIsCamera(true);
                    materialTexture->setImage(m_scene->getRealCamera().getImage());
                    materialChanged = true;
                }
                #endif

                ImGui::EndCombo();
            }
            break;
        }
        default:
            break;
        }
        return materialChanged;
    }

    bool SceneInteractive::guiEditMaterial(std::unique_ptr<IMaterial> &material)
    {
        bool materialChanged = false;
        if (ImGui::BeginTabItem("Material")) {
            if (changeMaterialType(material))
                materialChanged = true;
            if (customEditMaterial(material))
                materialChanged = true;
            // Diffuse
            float diffuse = material->getDiffuse();
            if (ImGui::SliderFloat("Diffuse", &diffuse, 0.0f, 1.0f)) {
                material->setDiffuse(diffuse);
                materialChanged = true;
            }
            // Specular
            float specular = material->getSpecular();
            if (ImGui::SliderFloat("Specular", &specular, 0.0f, 1.5f)) {
                material->setSpecular(specular);
                materialChanged = true;
            }
            // Shininess
            if (specular > 0) {
                float shininess = material->getShininess();
                if (ImGui::SliderFloat("Shininess", &shininess, 1.0f, 100.0f,
                "%.1f", ImGuiSliderFlags_Logarithmic)) {
                    material->setShininess(shininess);
                    materialChanged = true;
                }
            }
            // Reflection
            float reflection = material->getReflection();
            if (ImGui::SliderFloat("Reflection", &reflection, 0.0f, 1.0f)) {
                material->setReflection(reflection);
                materialChanged = true;
            }
            // Transparency
            float transparency = material->getTransparency();
            if (ImGui::SliderFloat("Transparency", &transparency, 0.0f, 1.0f)) {
                material->setTransparency(transparency);
                materialChanged = true;
            }
            // Refraction
            if (transparency > 0) {
                float refraction = material->getRefraction();
                if (ImGui::SliderFloat("Refraction", &refraction, 0.0f, 3.0f)) {
                    material->setRefraction(refraction);
                    materialChanged = true;
                }
            }
            ImGui::EndTabItem();
        }
        return materialChanged;
    }
} // namespace Raytracer
