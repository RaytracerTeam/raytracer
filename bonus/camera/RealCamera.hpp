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

            sf::Image getCurrentFrame();

            unsigned int getCamWidth() const { return m_camWidth; }
            unsigned int getCamHeight() const { return m_camHeight; }

            void setFrameToImage(cv::Mat &frame, sf::Image &image);
            void setEdgesToImage(cv::Mat &frame, sf::Image &image);

        protected:
        private:
            cv::VideoCapture m_camera;
            unsigned int m_camWidth;
            unsigned int m_camHeight;
            sf::Image m_image;
            cv::Mat cameraFrame;
            cv::Mat edges;
            sf::Uint8 *m_pixels;
    };
} // namespace Raytracer

