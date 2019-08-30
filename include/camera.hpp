#pragma once

#include <opencv2/opencv.hpp>

class Camera
{
public:
	virtual void start() = 0;
	virtual void getImage(cv::Mat& image) = 0;
	virtual void release() = 0;
};