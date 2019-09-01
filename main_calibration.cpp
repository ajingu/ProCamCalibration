#include <iostream>
#include <opencv2/structured_light.hpp>
#include "collect.hpp"

const std::string PATTERNS_DIR_PATH = "../data/pattern";
const std::string CAMERA_DIR_PATH = "../data/camera";
const std::string CORRESPONDENCE_C2P_X_PATH = "../data/correspondence/c2p_x.xml";
const std::string CORRESPONDENCE_C2P_Y_PATH = "../data/correspondence/c2p_y.xml";
const int PROJ_WIDTH = 1280;
const int PROJ_HEIGHT = 800;
const int CAM_WIDTH = 1920;
const int CAM_HEIGHT = 1080;
const int THRESH = 40;

int main()
{
	cv::structured_light::GrayCodePattern::Params params;
	params.width = PROJ_WIDTH;
	params.height = PROJ_HEIGHT;
	auto patterns = cv::structured_light::GrayCodePattern::create(params);

	std::vector<cv::Mat> camera_images;
	cv::Mat white, black;

	collect_images(CAMERA_DIR_PATH, camera_images);
	black = camera_images.back();
	camera_images.pop_back();
	white = camera_images.back();
	camera_images.pop_back();

	cv::Mat c2p_x = cv::Mat::zeros(CAM_HEIGHT, CAM_WIDTH, CV_16U);
	cv::Mat c2p_y = cv::Mat::zeros(CAM_HEIGHT, CAM_WIDTH, CV_16U);
	for (int y = 0; y < CAM_HEIGHT; y++)
	{
		for (int x = 0; x < CAM_WIDTH; x++)
		{
			cv::Point proj_pixel;
			if(white.at<cv::uint8_t>(y, x) - black.at<cv::uint8_t>(y, x) > THRESH &&
				!patterns->getProjPixel(camera_images, x, y, proj_pixel))
			{
				c2p_x.at<cv::uint16_t>(y, x) = proj_pixel.x;
				c2p_y.at<cv::uint16_t>(y, x) = proj_pixel.y;
			}
		}
	}

	cv::FileStorage fs_c2p_x(CORRESPONDENCE_C2P_X_PATH, cv::FileStorage::WRITE);
	cv::FileStorage fs_c2p_y(CORRESPONDENCE_C2P_Y_PATH, cv::FileStorage::WRITE);
	fs_c2p_x << "c2p_x" << c2p_x;
	fs_c2p_y << "c2p_y" << c2p_y;
	fs_c2p_x.release();
	fs_c2p_y.release();

	return 0;
}