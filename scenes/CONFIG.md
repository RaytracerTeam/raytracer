# Config

## Introduction

The configuration file is a file that will allow you to create your own scene. It is composed of several parts that will allow you to create a scene with the Here is your objects you want.

## Table of contents

- [Config](#config)
  - [Introduction](#introduction)
  - [Table of contents](#table-of-contents)
  - [Getting started](#getting-started)
  - [Structure](#structure)
    - [Global](#global)
    - [Light](#light)
    - [Primitives](#primitives)
  - [obj](#obj)
    - [Optimization](#optimization)
    - [Cameras](#cameras)
  - [Example](#example)

## Getting started

Here is a simple example of a configuration [config_example.cfg](config_example.cfg)

## Structure

To create your own scene, you will need to create a file with the extension `.cfg`. This file will be composed of several parts that will allow you to create your scene.

If you don't config a section, the program will use the default value of this section.

the sections are:
 - **global**
 - **light**
 - **primitives**
 - **obj**
 - **optimizations**
 - **camera** (For bonus)

### Global

The global part is the first section of the configuration file. It will allow you to define:
- The section skybox with `skybox = {}` 
  <details>
    <summary>Skybox section</summary>
    <li><code>hasTexture = bool;</code> -> If you apply a texture</li>
    <li><code>path = pathToImage;</code> -> add the path to tan image who will be the sky box | <i>pathToImage: float;</i></li>
    <li><code>color = {r = short, g = short, b = short };</code> -> add the color of the skybox</li>
</details>

- `speed = float;` -> The speed of the camera (_For the bonus_)
- `sensivity = float;` -> The sensivity of the mouse (_For the bonus_)

### Light

The light section is the second part of the configuration file. It will allow you to define:

- `lights: {};` -> The section to define all and all types of lights


- `ambientLight = {};` -> The secction to define the ambient light
---
  <details>
    <summary>Ambient light section</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> add the color of the ambient light</li>
    <li><code>intensity = float;</code> -> add the intensity of the ambient light</li>
</details>

---

- `pointLights = ();` -> The section to define all points light
  - `{},` -> The section to define a point light

---

  <details>
    <summary>Point light section</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> add the color of the point light</li>
    <li><code>intensity = float;</code> -> add the intensity of the point light</li>
    <li><code>position = {x = float; y = float; z = float;};</code> -> put the light at that position</li>
</details>

---

- `directionalLights = ()` -> The section to define all the directional lights
  - `{},` -> The section to define a directional light

---

  <details>
    <summary>Directional light section</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> add the color of the directional light</li>
    <li><code>intensity = float;</code> -> add the intensity of the directional light</li>
    <li><code>direction = {x = float; y = float; z = float;};</code> -> put the light at that direction</li>
</details>

---

### Primitives

The primitives section is the third part of the configuration file. It will allow you to define simple matematical forms:

`primitives = {}` -> The section to define all and all types of primitives

The groups names
- `spheres = ();`
- `planes = ();`
- `cubes = ();`
- `cylinders = ();`
- `cones = ();`
- `toruses = ();`
- `planes = ();`
- `tanglecubes = ();`
are defined as follows:

  - `{}` -> The section to define a primitive

---

  <details>
    <summary>Primitive section model</summary>
    <li><code>position = {x = short; y = short; z = short;};</code> -> The position of the primitive</li>
    <li><code>radius = float;</code> -> The scale of the primitive</li>
    <li><code>material = {};</code> -> The material of the primitive</li>

---

  <details>
    <summary>Material section</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> The color of the primitive</li>
    <li><code>texture = pathToImage;</code> -> The texture of the primitive</li>
    <li><code>type = type;</code> -> The type of the primitive | <i>type: string;</i></li>
  </details>
</details>

---

> **_Note:_** Some primitives have specific attributes, such as the `radius` for the sphere or the `size` for the cube. And planes doesn't have a radius, of course, but an `axis = "X"` (it can be X, Y or Z) and a `position = float;

## obj

The obj section is the fourth part of the configuration file. It will allow you to define the obj file you want to load:

- `obj = {};` -> The section to define all and all types of obj

  - `{},` -> The section to define a obj

---

  <details>
    <summary>Obj section model</summary>
    <li><code>path = pathToObj;</code> -> The path to the obj file | <i>pathToObj: string;</i></li>
    <li><code>position = {x = short; y = short; z = short;};</code> -> The position of the obj</li>
    <li><code>transformation = {};</code> -> The transformation of the obj</li>

---

  <details>
    <summary>Transformation section</summary>
    <li><code>scale = {x = short; y = short; z = short;};</code> -> The scale of the obj</li>
    <li><code>rotation = {x = short; y = short; z = short;};</code> -> The rotation of the obj</li>
  </details>

---

  <li><code>rotation = {x = short; y = short; z = short;};</code> -> The rotation of the obj</li>
  <li><code>material = {};</code> -> The material of the obj</li>

---

  <details>
    <summary>Material section</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> The color of the obj</li>
    <li><code>texture = pathToImage;</code> -> The texture of the obj</li>
    <li><code>type = type;</code> -> The type of the obj | <i>type: string;</i></li>
    <li><code>reflection = float;</code> -> The reflection of the obj</li>
  </details>
</details>

---

### Optimization

The optimization section is the fifth part of the configuration file. It will allow you to define the optimization of the scene:

- `optimizations : {};` -> The section to define all and all types of optimization

- `maxRayBounces = int;` -> The maximum number of ray bounces
- `useBVH = bool;` -> If you want to use the BVH
- `maxPrimitivesPerBVHNode = int;` -> The maximum number of primitives per BVH node
- `bvhAlgorithm = algorithm;` -> The algorithm of the BVH | <i>algorithm: "sah" | "median";</i>
- `useMultithreading = bool;` -> If you want to use multithreading
- `useGPU = bool;` -> If you want to use the GPU


### Cameras

The camera section is the sixth and last part of the configuration file. It will allow you to define the camera of the scene:

- `cameras = ();` -> The section to define all and all types of cameras

  - `{}` -> The section to define a camera
  - `position = {x = short; y = short; z = short;};` -> The position of the camera
  - `rotation = {x = short; y = short; z = short;};` -> The rotation of the camera
  - fieldOfView = float; -> The field of view of the camera
  - `resolution = float;` -> Resolution of the camera

## Example

Here is an example of a configuration file:

```cfg
global = {
    skybox = {
        hasTexture = false;
        color = {r = 0; g = 0; b = 144};
    };
    speed = 0.1;
    sensivity = 0.1;
};

cameras:
(
    {
        resolution = 400;
        position = { x = 0.85; y = 4.2; z = 7.93; };
        fieldOfView = 50.82; # In degree
    },
);

lights: {
    ambientLight = {
        color = {r = 255; g = 255; b = 255};
        intensity = 0.5;
    };
    pointLights = (
        {
            color = {r = 255; g = 255; b = 255};
            intensity = 1.;
            position = {x = 0; y = 0; z = 0};
        },
    );
    directionalLights = (
        {
            color = {r = 255; g = 255; b = 255};
            intensity = 0.5;
            direction = {x = 0; y = 0; z = 0};
        },
    );
};

primitives = {
    spheres = (
      {
          position = { x = -1.; y = 1.2; z = -2.; }; radius = 1.; material = { type = "solid_color"; color = { r = 0; g = 255; b = 255; }; };
      },
      {
        position = { x = -5.; y = 10.2; z = -6.; }; radius = 1.; material = { type = "solid_color"; color = { r = 255; g = 0; b = 255; }; };
      }
    );
    planes = (
      {
          position = 0.; axis = "Y"; material = { type = "solid_color"; color = { r = 255; g = 255; b = 255; }; };
      },
    );
};
```
