# Add a primitive to the project

To add a primitive to the parsing, saving and editing, you need to follow these steps:

This example is for a Sphere.


## Parsing and Saving

```cpp
// ADD IN include/Scene/Primitives/AllSpheres.hpp

// ...
#include "Scene/Primitives/Sphere.hpp"
// ...
```

```cpp
// ADD IN include/Parsing/Parsing.hpp

// ...
void parseSphere(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene);
// ...

// ...
void saveSphere(libconfig::Setting &list, Sphere *sphere);
// ...
```

```cpp
// CREATE FILE IN src/parsing/primitives/parseSpheres.cpp

/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** parseSphere
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Materials/MaterialSolid.hpp"
#include "Scene/Primitives/Sphere.hpp"

void Raytracer::Parsing::parseSpheres(const libconfig::Setting &primitiveSetting, std::unique_ptr<Scene> &scene)
{
    if (!primitiveSetting.exists(CFG_SPHERES))
        return;
    for (const auto &config : primitiveSetting.lookup(CFG_SPHERES)) {
        auto sphere = std::make_unique<Sphere>(parsePosition(config),
            parseMaterial(config),
            parseRadius(config));
        scene->addPrimitive(std::move(sphere));
    }
}

```

```cpp
// ADD IN src/parsing/primitives/parsePrimitives.cpp

// ...
parseSpheres(primitiveSetting, scene);
// ...
```

```cpp
// CREATE FILE IN src/saving/primitives/saveSphere.cpp

/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** saveSphere
*/

#include "Parsing/Parsing.hpp"

#include "Scene/Primitives/Sphere.hpp"

#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void Parsing::saveSphere(libconfig::Setting &list, Sphere *sphere)
    {
        libconfig::Setting &setting = list.add(libconfig::Setting::TypeGroup);

        savePos(setting, sphere->getOrigin());

        libconfig::Setting &sphereRadius = setting.add(CFG_RADIUS, libconfig::Setting::TypeFloat);
        sphereRadius = sphere->getRadius();

        saveMaterial(setting, torus);
    }
} // namespace Raytracer
```

```cpp
// ADD IN src/scene/parsing/savePrimitives.cpp

// ...
libconfig::Setting &sphereList = primitivesSetting.add(CFG_SPHERES, libconfig::Setting::TypeList);
// ...

// ...
case PrimitiveType::SPHERE:
    saveSphere(sphereList, static_cast<Sphere *>(primitive.get()));
    break;
// ...
```

## Editing

```cpp
// ADD IN include/Scene/Interactive/SceneInteractive.hpp

// ...
void editSphere(Sphere *sphere);
// ...
```

```cpp
// CREATE FILE IN src/scene/interactive/imgui/primitives/editSphere.cpp

/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** editSphere
*/

#include "Scene/Interactive/SceneInteractive.hpp"

#include "Scene/Primitives/Sphere.hpp"
#include "Scene/Materials/MaterialSolid.hpp"

namespace Raytracer
{
    void SceneInteractive::editSphere(Sphere *sphere)
    {
        (void)sphere;
        #ifdef BONUS
        float sphereRadius = sphere->getRadius();
        if (ImGui::SliderFloat("Radius", &sphereRadius, DEFAULT_RADIUS_MIN,
        DEFAULT_RADIUS_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            sphere->setRadius(sphereRadius);
            m_needRendering = true;
        }
        #endif
    }
} // namespace Raytracer

```

```cpp
// ADD IN src/scene/interactive/imgui/primitives/guiEditPrimitives.cpp

// ...
case PrimitiveType::SPHERE:
    editSphere(static_cast<Sphere *>(primitive.get()));
    break;
// ...
```

## Add the primitive with the GUI

```cpp
// ADD IN src/scene/interactive/imgui/guiAddPrimitives.cpp

// ...
if (ImGui::Selectable("Sphere")) {
    auto sphere = std::make_unique<Sphere>(
        Math::Vector3D(0, 0, 0),
        std::make_unique<MaterialSolid>(Color(255U, 255, 255)), 1.0);
    sphere->setID(m_scene->getPrimitives().size() + 1);
    m_scene->addPrimitive(std::move(sphere));
    m_needRendering = true;
    m_updateBVH = true;
}
// ...
```
