#include "webcamera.hpp"

WebCamera::WebCamera(int width, int height) : width(width), height(height){}

void WebCamera::start()
{
	camera = cv::VideoCapture(0);
	camera.set(cv::CAP_PROP_FRAME_WIDTH, width);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, height);

	if (!camera.isOpened())
	{
		std::cerr << "Camera is not opened." << std::endl;
		std::exit(1);
	}
}

void WebCamera::getImage(cv::Mat& image)
{
	camera >> image;
}

void WebCamera::release()
{
	camera.release();
}