# Scene Configuration

## Introduction

The configuration file is a file that **contains** all of the **informations** of a **scene**.

It is composed of several parts that will allow you to create your own scene.

## Table of contents

- [Scene Configuration](#scene-configuration)
  - [Introduction](#introduction)
  - [Table of contents](#table-of-contents)
  - [Getting started](#getting-started)
- [Structure](#structure)
  - [Global](#global)
    - [Optimization](#optimization)
  - [Cameras](#cameras)
  - [Primitives](#primitives)
  - [Lights](#lights)
  - [Objs](#objs)
  - [Inventory](#inventory)
- [Example](#example)

## Getting started

Here is a simple example of a configuration [config_example.cfg](config_example.cfg)

# Structure

To create your own scene, you will need to create a file with the extension `.cfg`. This file will be composed of several parts that will allow you to create your scene.

If you don't name an object or a list, the program will use the default value.

the objects are:
 - **global {}**
 - **optimizations {}**
 - **cameras ()**
 - **primitives ()**
 - **lights ()**
 - **objs ()**

## Global
- `global = {};` -> Object that define the global settings
  - `skybox = {}` 
    <details>
      <summary>Skybox</summary>
      <li><code>hasTexture = bool;</code> -> If you apply a texture</li>
      <li><code>path = string;</code> -> If the Skybox has a texture, this will be the path to that texture
      <li><code>color = {r = short, g = short, b = short };</code> -> add the color of the skybox</li>
  </details>

  - `speed = float;` -> The speed of the camera (_Interactive mode_)
  - `sensivity = float;` -> The sensivity of the mouse (_Interactive mode_)

### Optimization
- `optimization = {};` -> Object that define optimizations

  - `maxRayBounces = int;` -> The maximum number of ray bounces
  - `useBVH = bool;` -> If you want to use the BVH
  - `maxPrimitivesPerBVHNode = unsigned int;` -> The maximum number of primitives per BVH node
  - `useMultithreading = bool;` -> If you want to use multithreading
  - `useGPU = bool;` -> If you want to use the GPU (WIP)

## Cameras

- `cameras = ();` -> Array that define cameras in the scene.

  - `{}` -> Object that define a camera
  - `position = {x = short; y = short; z = short;};` -> The position of the camera
  - `rotation = {x = short; y = short; z = short;};` -> The rotation of the camera
  - fieldOfView = float; -> The field of view of the camera
  - `resolution = float;` -> Resolution of the camera

## Primitives

`primitives = ()` -> Array that define all types of primitives

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

  - `{}` -> The object to define a primitive

---

  <details>
    <summary>Primitive object model</summary>
    <li><code>position = {x = short; y = short; z = short;};</code> -> The position of the primitive</li>
    <li><code>radius = float;</code> -> The scale of the primitive</li>
    <li><code>material = {};</code> -> The material of the primitive</li>
  </details>

---

  <details>
    <summary>Material object</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> The color of the primitive</li>
    <li><code>texture = pathToImage;</code> -> The texture of the primitive</li>
    <li><code>type = type;</code> -> The type of the primitive | <i>type: string;</i></li>
    <li><code>diffuse = float;</code> -> The diffuse of the obj</li>
    <li><code>specular = float;</code> -> The specular of the obj</li>
    <li><code>shininess = float;</code> -> The shininess of the obj</li>
    <li><code>reflection = float;</code> -> The reflection of the obj</li>
    <li><code>transparency = float;</code> -> The transparency of the obj</li>
    <li><code>refraction = float;</code> -> The refraction of the obj</li>
  </details>

---

> **_Note:_** Some primitives have specific attributes, such as the `radius` for the sphere or the `size` for the cube. And planes doesn't have a radius, of course, but an `axis = "X"` (it can be X, Y or Z) and a `position = float;


## Lights

- `ambientLight = ();` -> Array that define ambient lights
  <details>
    <summary>Ambient light</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> add the color of the ambient light</li>
    <li><code>intensity = float;</code> -> add the intensity of the ambient light</li>
</details>

---

- `pointLights = ();` -> Array that define point lights
  - `{},` -> The object to define a point light

  <details>
    <summary>Point light</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> add the color of the point light</li>
    <li><code>intensity = float;</code> -> add the intensity of the point light</li>
    <li><code>position = {x = float; y = float; z = float;};</code> -> put the light at that position</li>
</details>

---

- `directionalLights = ()` -> Object that define the directional lights
  - `{},` -> The object to define a directional light

  <details>
    <summary>Directional light</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> add the color of the directional light</li>
    <li><code>intensity = float;</code> -> add the intensity of the directional light</li>
    <li><code>direction = {x = float; y = float; z = float;};</code> -> put the light at that direction</li>
</details>

## Objs

- `obj = ();` -> Array that define all and all types of obj

  - `{},` -> The object to define a obj file.

---

  <details>
    <summary>Obj object model</summary>
    <li><code>path = pathToObj;</code> -> The path to the obj file | <i>pathToObj: string;</i></li>
    <li><code>position: {x = short; y = short; z = short;};</code> -> The position of the obj</li>
    <li><code>transformation = {};</code> -> The transformation of the obj</li>

---

  <details>
    <summary>Transformation object</summary>
    <li><code>scale : {x = short; y = short; z = short;};</code> -> The scale of the obj</li>
    <li><code>rotation : {x = short; y = short; z = short;};</code> -> The rotation of the obj</li>
  </details>

---

  <li><code>material = {};</code> -> The material of the obj</li>

---

  <details>
    <summary>Material object</summary>
    <li><code>color = {r = short; g = short; b = short;};</code> -> The color of the obj</li>
    <li><code>texture = pathToImage;</code> -> The texture of the obj</li>
    <li><code>type = type;</code> -> The type of the obj | <i>type: string;</i></li>
    <li><code>diffuse = float;</code> -> The diffuse of the obj</li>
    <li><code>specular = float;</code> -> The specular of the obj</li>
    <li><code>shininess = float;</code> -> The shininess of the obj</li>
    <li><code>reflection = float;</code> -> The reflection of the obj</li>
    <li><code>transparency = float;</code> -> The transparency of the obj</li>
    <li><code>refraction = float;</code> -> The refraction of the obj</li>
  </details>
</details>

## Inventory

- `inventory = ();` -> Array that define all and all types of obj

  - `{},` -> The object to define a material

Each object in this array is an item that you have in your inventory.
You can access your inventory items with the digits of your keyboard.


# Example

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
