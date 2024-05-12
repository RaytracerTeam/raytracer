/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** parseAndSaveInteractive.cpp
*/

/*
#include "Scene/Interactive/SceneInteractive.hpp"

namespace Raytracer {
    void SceneInteractive::parseInteractive(const std::string &filename)
    {
        try {
            m_cfg.readFile(filename.c_str());
        } catch (libconfig::ParseException &e) {
            throw Error(e.getError(), "Parsing::parse");
        }
        libconfig::Setting &root = m_cfg.getRoot();
        if (root.exists(CFG_INTERACTIVE)) {
            libconfig::Setting &interactive = root["interactive"];
            if (interactive.exists(CFG_SPEED)) {
                m_movementSpeed = interactive[CFG_SPEED];
                m_defaultMovementSpeed = m_movementSpeed;
            }
            if (interactive.exists(CFG_SENSITIVITY)) {
                m_rotationSpeed = interactive[CFG_SENSITIVITY];
            }
            if (interactive.exists(CFG_ALWAYS_RENDER)) {
                m_alwaysRender = interactive[CFG_ALWAYS_RENDER];
            }
        }
        if (root.exists(CFG_OBJ)) {
            m_objFound = true;
        }
    }

    void SceneInteractive::saveInteractive(const std::string &filename)
    {
        libconfig::Config cfg;
        try {
            cfg.readFile(filename.c_str());
        } catch (libconfig::ParseException &e) {
            throw Error(e.getError(), "Parsing::save");
        }

        libconfig::Setting &root = cfg.getRoot();



        libconfig::Setting &root = m_cfg.getRoot();
        libconfig::Setting &interactive = root.add(CFG_INTERACTIVE, libconfig::Setting::TypeGroup);
        interactive.add(CFG_SPEED, libconfig::Setting::TypeFloat) = m_movementSpeed;
        interactive.add(CFG_SENSITIVITY, libconfig::Setting::TypeFloat) = m_rotationSpeed;
        interactive.add(CFG_ALWAYS_RENDER, libconfig::Setting::TypeBoolean) = m_alwaysRender;
        if (m_objFound) {
            root.add(CFG_OBJ, libconfig::Setting::TypeBoolean) = true;
        }
        m_cfg.writeFile(filename.c_str());
    }
} // namespace Raytracer
*/
