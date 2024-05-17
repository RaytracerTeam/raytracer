# Raytracer

## Introduction

This is the Raytracer project, an Epitech project from the **OOP module** (Object Oriented Programming).

The objective is to build a 3D scene with light rays generate beautiful images.

We pushed the idea a little further with an _interactive scene_ that _creates, edit and delete primitives_, _loads objfile_, _saves image_ **in runtime**. See [Features](#features).

## Requirements

Be sure to have install **libconfig++**

Debian/ubuntu install :
```bash
sudo apt install libconfig++-dev
```

Arch install:
```bash
sudo pacman -S libconfig
```
Since ImGui isn't natively supporting SFML, you need to install the following dependencies :

- **glew**
- **glfw**

For Fedora :
```bash
sudo dnf install glew glfw
```

For Arch :
```bash
sudo pacman -S glew glfw
```

## Getting started

First of all you will need to compile the project, for that you can write in your terminal

```bash
make
```

or if you want a way more impressive demo, you can write in your terminal

```bash
make bonus
```

or if you love yourself and want to watch you in our incredible raytracer, you can write in your terminal

```bash
make bonusbonus
```

> **_Note:_** To change from normal interface to bonus interface or from bonus to normal, you need to apply clean your repository with `make fclean`

and now you can lauch it with :

```bash
./raytracer scenes/config_example.cfg
```

to have a picture in *.ppm*. If you want to have it in *.png* you can do the command

```bash
./raytracer && ffmpeg -y -i out.ppm out.png && xdg-open out.png
```

And if you want to have the interractive mode, you can add the `-i` option like :

```bash
./raytracer -i scenes/config_example.cfg
```

and if you want to recovered an old scene, you can do the command

```bash
./raytracer -i scenes/quicksave.cfg
```

## Config

To have all the information about the config file, you can check the [CONFIG.md](scenes/CONFIG.md) file.

## Documentation

To build the documentation, you can do the command

```bash
make doc
```

and to run it, you can do the command

```bash
make rundoc
```

## Bonus

[ImGui](https://github.com/ocornut/imgui) used with [ImGuiSfml](https://github.com/SFML/imgui-sfml) to create a GUI in SFML that allows to **edit the scene** in real time and **save it**, and more, check the shortcuts!

<details>
    <summary><b>Keybinds (by default)</b></summary>
    <h2> Move in the scene </h2>
    <table>
    <caption><h3>Move in the scene</h3></caption>
    <thread>
        <tr>
            <th>Key</th>
            <th>Action</th>
        </tr>
    </thread>
    <tbody>
        <tr>
            <td><b>Z</b></td>
            <td>Move forward</td>
        </tr>
        <tr>
            <td><b>Q</b></td>
            <td>Move left</td>
        </tr>
        <tr>
            <td><b>S</b></td>
            <td>Move backward</td>
        </tr>
        <tr>
            <td><b>D</b></td>
            <td>Move right</td>
        </tr>
        <tr>
            <td><b>Space bar</b></td>
            <td>Move up</td>
        </tr>
        <tr>
            <td><b>Left Shift</b></td>
            <td>Move down</td>
        </tr>
        <tr>
            <td><b>U</b></td>
            <td>Rotate up</td>
        </tr>
        <tr>
            <td><b>J</b></td>
            <td>Rotate down</td>
        </tr>
        <tr>
            <td><b>H</b></td>
            <td>Rotate left</td>
        </tr>
        <tr>
            <td><b>K</b></td>
            <td>Rotate right</td>
        </tr>
        <tr>
            <td><b>Left Control</b></td>
            <td>Sprint</td>
        </tr>
    </tbody>
    </table>
    <table>
    <caption><h3>Interact with the scene<h3></caption>
    <thread>
        <tr>
            <th>Key</th>
            <th>Action</th>
            <th>In <i>Minecraft mode</i></th>
        </tr>
    </thread>
    <tbody>
        <tr>
            <td><b>M</b></td>
            <td>Switch to <i>Minecraft mode</i></td>
            <td>Goes back to normal mode</td>
        </tr>
        <tr>
            <td><b>Left click</b></td>
            <td></td>
            <td>Destroy minecraft block</td>
        </tr>
        <tr>
            <td><b>Right click</b></td>
            <td>Use simple mouse to rotate the camera</td>
            <td>Place minecraft block</td>
        </tr>
        <tr>
            <td><b>G / Middle click</b></td>
            <td>Select primitive at the center of the screen (in bonus mode)</td>
            <td><i>Same behavior</i></td>
        </tr>
        <tr>
            <td><b>R</b></td>
            <td>Draw spheres at the reach distance</td>
            <td><i>Same behavior</i></td>
        </tr>
        <tr>
            <td><b>0-9</b></td>
            <td></td>
            <td>Change the selected Material of your inventory</td>
        </tr>
    </tbody>
    </table>
    <table>
    <caption><h3>Save and quit</h3></caption>
    <thread>
        <tr>
            <th>Key</th>
            <th>Action</th>
        </tr>
    </thread>
    <tbody>
        <tr>
            <td><b>Escape</b></td>
            <td>Exit (and saves your scene in <i>scenes/temp.cfg</i>)</td>
        </tr>
        <tr>
            <td><b>C</b></td>
            <td>Save scene to the opened one and exit</td>
        </tr>
        <tr>
            <td><b>X</b></td>
            <td>Quick save and exit (in <i>scenes/quick_save.cfg</i>)</td>
        </tr>
    </tbody>
    </table>
    <table>
    <caption><h3>Other</h3></caption>
    <thread>
        <tr>
            <th>Key</th>
            <th>Action</th>
        </tr>
    </thread>
    <tbody>
        <tr>
            <td><b>F2</b></td>
            <td>Take a screenshot (saved in screenshots/171503-.png</td>
        </tr>
        <tr>
            <td><b>F3</b></td>
            <td>Toggle debug tab</td>
        </tr>
        <tr>
            <td><b>Delete</b></td>
            <td>Remove selected object (it has to be selected in the GUI)</td>
        </tr>
        <tr>
            <td><b>F</b></td>
            <td>Toggle fullscreen</td>
        </tr>
        <tr>
            <td><b>O</b></td>
            <td>Reset camera to the loaded position</td>
        </tr>
    </tbody>
    </table>
</details>

> **_Note:_** You can change the keybinds in `config/keys.cfg` file.

> **_Attention:_** If you **messed up your config**, delete it and it will be recreated with default values.

## Features

### Primitives
- [x] **Sphere**
- [x] **Plane**
- [x] **Cylinder**
- [x] **Cone**
- [x] **Limited Cylinder**
- [x] **Limited Cone**
- [x] **Triangle**
- [x] **Cube**
- [x] **Torus**
- [x] **Tanglecube**
- [x] **Objfile** (with textures)
- [ ] **Mobius strip**
- [ ] **Fractals**

### Lights
- [x] **Point light**
- [x] **Directional light**
- [x] **Ambient light**
- [x] **Drop shadows**
- [x] **Multiple ambient lights**
- [x] **Multiple directional lights**
- [x] **Multiple point lights**
- [x] **Colored light**
- [x] **Phong reflection model**
- [ ] **Ambient occlusion**

### Materials
- [x] **Flat color**
- [x] **Transparency**
- [x] **Refraction**
- [x] **Reflection**
- [x] **Refraction**
- [x] **Texturing from file** (on Spheres, Cubes, Triangles and Plane)
- [x] **Texturing from procedural generation of chessboard** (with any size and color)
- [ ] **Texturing from procedural generation of Perlin noise**

### Transformations
- [x] **Translation**
- [x] **Rotation**
- [x] **Scale**
- [ ] **Scene graph**

### Scene configuration
- [x] **Add primitives to the scene** (including objfile)
- [x] **Set up lightning**
- [x] **Set up camera**

#### Bonus
Can configure in real time with ImGui
See [CONFIG.md](scenes/CONFIG.md)
- [x] Skybox
- [x] Inventory
- [x] Cube Primitive
- [x] Minecraft mode
- [x] Save scene
- [x] Cinematic mode
- [x] Texture camera in bonusbonus

### Optimization
- [x] **Space partitioning** (bounding boxes)
- [x] **Multithreading**
- [ ] **Clustering**
