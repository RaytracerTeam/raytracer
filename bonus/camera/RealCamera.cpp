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
        if (!m_camera.isOpened()) {
            std::cerr << "Camera failed to open" << std::endl;
        }
        m_camWidth = (unsigned int)m_camera.get(cv::CAP_PROP_FRAME_WIDTH);
        m_camHeight = (unsigned int)m_camera.get(cv::CAP_PROP_FRAME_HEIGHT);
        m_image.create(m_camWidth, m_camHeight);
        m_pixels = (sf::Uint8 *)malloc(sizeof(sf::Uint8) * m_camWidth * m_camHeight);
    }

    RealCamera::~RealCamera()
    {
        if (m_camera.isOpened())
            m_camera.release();
        free(m_pixels);
    }

    void RealCamera::setFrameToImage(cv::Mat &frame, sf::Image &image)
    {
        for (int i = 0; i < frame.cols; i++) {
            for (int j = 0; j < frame.rows; j++) {
                sf::Color color(frame.at<cv::Vec3b>(j, i)[0],
                                frame.at<cv::Vec3b>(j, i)[1],
                                frame.at<cv::Vec3b>(j, i)[2]);
                image.setPixel(i, j, color);
            }
        }
    }

    void RealCamera::setEdgesToImage(cv::Mat &frame, sf::Image &image)
    {
        for (int i = 0; i < frame.cols; i++) {
            for (int j = 0; j < frame.rows; j++) {
                sf::Color color(frame.at<uchar>(j, i),
                                frame.at<uchar>(j, i),
                                frame.at<uchar>(j, i));
                image.setPixel(i, j, color);
            }
        }
    }

    sf::Image RealCamera::getCurrentFrame()
    {
        m_camera >> cameraFrame;
        // cv::flip(cameraFrame, cameraFrame, -1);
        cv::cvtColor(cameraFrame, cameraFrame, cv::COLOR_BGR2RGB);
        setFrameToImage(cameraFrame, m_image);
        return m_image;
    }
} // namespace Raytracer
