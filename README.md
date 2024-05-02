# Raytracer

Debian/ubuntu install :
```bash
sudo apt install libconfig++-dev
```


## Demo :

./raytracer && ffmpeg -y -i out.ppm out.png && xdg-open out.png

> **_Note:_** The demo is much more impressive with the bonus, check it out !


## Bonus :

[ImGui](https://github.com/ocornut/imgui) used with [ImGuiSfml](https://github.com/SFML/imgui-sfml) to create a GUI in SFML that allows to **edit the scene** in real time and **save it**.

### Requires

Since ImGui isn't natively supporting SFML, you need to install the following dependencies :

For Fedora :
```bash
sudo dnf install glew glfw
```

### Run with bonus
```bash
make fclean # clean the project if already compiled
make bonus
./raytracer -i scenes/quick_save.cfg
```
