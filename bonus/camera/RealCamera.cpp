/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RealCamera
*/

#include "RealCamera.hpp"

namespace Raytracer
{
    RealCamera::RealCamera()
    {
    }

    void RealCamera::init(void)
    {
        m_camera = cv::VideoCapture(0, cv::CAP_AVFOUNDATION);
        m_image = std::make_shared<sf::Image>();
        if (!m_camera.isOpened()) {
            std::cerr << "Camera failed to open" << std::endl;
            return;
        }
        m_isCameraOpen = true;
        m_camWidth = (unsigned int)m_camera.get(cv::CAP_PROP_FRAME_WIDTH);
        m_camHeight = (unsigned int)m_camera.get(cv::CAP_PROP_FRAME_HEIGHT);
        m_image->create(m_camWidth, m_camHeight);
    }

    RealCamera::~RealCamera()
    {
        if (m_camera.isOpened())
            m_camera.release();
    }

    void RealCamera::setFrameToImage(void)
    {
        for (int i = 0; i < cameraFrame.cols; i++) {
            for (int j = 0; j < cameraFrame.rows; j++) {
                sf::Color color(cameraFrame.at<cv::Vec3b>(j, i)[0],
                                cameraFrame.at<cv::Vec3b>(j, i)[1],
                                cameraFrame.at<cv::Vec3b>(j, i)[2]);
                m_image->setPixel(i, j, color);
            }
        }
    }

    void RealCamera::setEdgesToImage(void)
    {
        cv::Canny(cameraFrame, edges, 100, 250);
        for (int i = 0; i < edges.cols; i++) {
            for (int j = 0; j < edges.rows; j++) {
                sf::Color color(edges.at<uchar>(j, i),
                                edges.at<uchar>(j, i),
                                edges.at<uchar>(j, i));
                m_image->setPixel(i, j, color);
            }
        }
    }

    sf::Image RealCamera::update()
    {
        if (!m_isCameraOpen)
            return *m_image;
        m_camera >> cameraFrame;
        // cv::flip(cameraFrame, cameraFrame, -1);
        cv::cvtColor(cameraFrame, cameraFrame, cv::COLOR_BGR2RGB);
        setFrameToImage();
        return *m_image;
    }
} // namespace Raytracer
