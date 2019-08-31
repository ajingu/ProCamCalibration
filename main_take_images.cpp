#include "collect.hpp"
#include "webcamera.hpp"

const std::string PATTERNS_DIR_PATH = "../data/pattern";
const std::string SAVE_DIR_PATH = "../data/camera";
const std::string PATTERN_WINDOW_NAME = "Pattern";
const std::string CAMERA_WINDOW_NAME = "Camera";
const int PROJ_WIDTH = 1280;
const int PROJ_HEIGHT = 800;
const int CAM_WIDTH = 1920;
const int CAM_HEIGHT = 1080;


std::string buildSaveImgPath(int index)
{
	std::string index_str =std::to_string(index);

	if (index < 10)
	{
		index_str = "0" + index_str;
	}

	return SAVE_DIR_PATH + "/camera" + index_str + ".png";
}


int main()
{
	std::vector<cv::Mat> patterns;
	collect_images(PATTERNS_DIR_PATH, patterns);

	WebCamera camera = WebCamera(CAM_WIDTH, CAM_HEIGHT);
	camera.start();

	cv::Mat camera_img;
	while (true)
	{
		if (cv::waitKey(10) == 'q')
		{
			break;
		}

		camera.getImage(camera_img);
		cv::imshow(CAMERA_WINDOW_NAME, camera_img);
	}
	cv::destroyAllWindows();

	
	cv::namedWindow(PATTERN_WINDOW_NAME, cv::WINDOW_NORMAL);
	cv::resizeWindow(PATTERN_WINDOW_NAME, PROJ_WIDTH, PROJ_HEIGHT);
	cv::setWindowProperty(PATTERN_WINDOW_NAME, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
	for(int idx = 0; idx < patterns.size(); idx++)
	{
		cv::imshow(PATTERN_WINDOW_NAME, patterns[idx]);
		if (cv::waitKey(500) == 'q')
		{
			break;
		}
		camera.getImage(camera_img);
		cv::imwrite(buildSaveImgPath(idx), camera_img);
	}
	cv::destroyAllWindows();

	return 0;
}