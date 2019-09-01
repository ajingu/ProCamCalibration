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
const int PROJ_SCREEN_POS_X = 1920;
const int PROJ_SCREEN_POS_Y = 0;

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
	cv::moveWindow(PATTERN_WINDOW_NAME, PROJ_SCREEN_POS_X, PROJ_SCREEN_POS_Y);
	cv::setWindowProperty(PATTERN_WINDOW_NAME, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
	for(int idx = 0; idx < patterns.size(); idx++)
	{
		cv::imshow(PATTERN_WINDOW_NAME, patterns[idx]);
		if (cv::waitKey(500) == 'q')
		{
			break;
		}
		camera.getImage(camera_img);

		std::ostringstream stream;
		stream << SAVE_DIR_PATH << "/camera" << std::setfill('0') << std::setw(2) << idx << ".png";
		cv::imwrite(stream.str(), camera_img);
	}
	cv::destroyAllWindows();

	return 0;
}