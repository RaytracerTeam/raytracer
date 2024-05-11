/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RealCamera
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

namespace Raytracer
{
    class RealCamera {
        public:
            RealCamera();
            ~RealCamera();

            void init(void);

            sf::Image update(void);

            std::shared_ptr<sf::Image> getImage(void) const { return m_image; }
            bool isCameraOpen(void) const { return m_isCameraOpen; }

            unsigned int getCamWidth() const { return m_camWidth; }
            unsigned int getCamHeight() const { return m_camHeight; }

            void setFrameToImage(void);
            void setEdgesToImage(void);

        protected:
        private:
            cv::VideoCapture m_camera;
            bool m_isCameraOpen = false;
            unsigned int m_camWidth;
            unsigned int m_camHeight;
            std::shared_ptr<sf::Image> m_image;
            cv::Mat cameraFrame;
            cv::Mat edges;
    };
} // namespace Raytracer

