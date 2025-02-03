#include "RealCamera.hpp"

void setFrameToImage(cv::Mat &frame, sf::Image &image)
{
        for (int i = 0; i < frame.cols; i++) {
                for (int j = 0; j < frame.rows; j++) {
                        sf::Color color(frame.at<cv::Vec3b>(j, i)[0],
                                        frame.at<cv::Vec3b>(j, i)[1],
                                        frame.at<cv::Vec3b>(j, i)[2]);
                        image.setPixel(sf::Vector2u(i, j), color);
                }
        }
}

void setEdgesToImage(cv::Mat &edges, sf::Image &image)
{
        for (int i = 0; i < edges.cols; i++) {
                for (int j = 0; j < edges.rows; j++) {
                        sf::Color color(edges.at<uchar>(j, i),
                                        edges.at<uchar>(j, i),
                                        edges.at<uchar>(j, i));
                        image.setPixel(sf::Vector2u(i, j), color);
                }
        }
}

// int main()
// {
//         cv::VideoCapture cap(0, cv::CAP_AVFOUNDATION);
//         if (!cap.isOpened()) {
//                 std::cout << "Camera failed to open" << std::endl;
//         }
//         sf::RenderWindow window(sf::VideoMode(1280, 720), "???");
//         sf::Image image;
//         image.create(1280, 720);
//         sf::Texture imageTexture;
//         imageTexture.create(1280, 720);
//         sf::Event event;
//         cv::Mat cameraFrame;
//         cv::Mat edges;

//         window.setFramerateLimit(30);
//         while (window.isOpen()) {
//                 cap >> cameraFrame;
//                 cv::flip(cameraFrame, cameraFrame, 1);
//                 cv::cvtColor(cameraFrame, cameraFrame, cv::COLOR_BGR2RGB);
//                 cv::Canny(cameraFrame, edges, 100, 250);
//                 // setFrameToImage(edges, image);
//                 setEdgesToImage(edges, image);

//                 while (window.pollEvent(event)) {
//                         if (event.type == sf::Event::EventType::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//                                 window.close();
//                 }
//                 window.clear();
//                 imageTexture.update(image);
//                 sf::Sprite sprite(imageTexture);
//                 window.draw(sprite);
//                 window.display();
//         }
//         cap.release();
//         return 0;
// }

int main()
{
    Raytracer::RealCamera camera;
    camera.init();
    sf::RenderWindow window(sf::VideoMode(camera.getCamWidth(), camera.getCamHeight()), "Real Camera");
    window.setFramerateLimit(30);
    sf::Image image;
    sf::Texture imageTexture;
    imageTexture.create(camera.getCamWidth(), camera.getCamHeight());

    std::shared_ptr<sf::Image> myImage = camera.getImage();

    image = camera.update();
    while (window.isOpen()) {
        imageTexture.update(*myImage);
        while (window.pollEvent(event)) {
            if (event.is<sf::Event::Closed> || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        sf::Sprite sprite(imageTexture);
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
