#pragma once

#include <iostream>
#include "camera.hpp"

class WebCamera : public Camera
{
private:
	cv::VideoCapture camera;
	int width;
	int height;

public:
	WebCamera(int width, int height);
	void start() override;
	void getImage(cv::Mat& image) override;
	void release() override;
};
