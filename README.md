# Raytracer

## Introduction

This is the Raytracer project, an **OOP project**, where the objective is to build a scene and to have an image from it. We push the idea a little further, so we added some features like _interactive scene_, on the interractive scene being able to _create primitives_, _loading objfile_, _saving image_, all that **in runtime**, etc.

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


## Bonus :

[ImGui](https://github.com/ocornut/imgui) used with [ImGuiSfml](https://github.com/SFML/imgui-sfml) to create a GUI in SFML that allows to **edit the scene** in real time and **save it**, and more, check the shortcuts!

<details>
    <summary>Shortcuts default</summary>
    <li><b>W:</b> move forward</li>
    <li><b>S:</b> move backward</li>
    <li><b>A:</b> move left</li>
    <li><b>D:</b> move right</li>
    <li><b>Space bar:</b> move up</li>
    <li><b>Left Shift:</b> move down</li>
    <li><b>U:</b> rotate up</li>
    <li><b>J:</b> rotate down</li>
    <li><b>H:</b> rotate left</li>
    <li><b>K:</b> rotate right</li>
    <li><b>Left Controle:</b> sprint</li>
    <li><b>Escape:</b> exit</li>
    <li><b>C:</b> save scene and exit</li>
    <li><b>X:</b> Quick save and exit</li>
    <li><b>F3:</b> Show debug</li>
    <li><b>F2:</b> Screenshot</li>
    <li><b>Delete:</b> remove selected object</li>
    <li><b>F11:</b> toggle fullscreen</li>
    <li><b>M:</b> toggle mouse / normal mode</li>
    <li><b>N:</b> Toggle simple mouse / normal mode</li>
    <li><b>O:</b> Reset</li>
</details>

Of course, you can change the shortcuts in the `config/keys_exemple.cfg` file.
