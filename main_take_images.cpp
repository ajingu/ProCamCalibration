#include "const.hpp"
#include "collect.hpp"
#include "webcamera.hpp"

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
		stream << CAMERA_DIR_PATH << "/camera" << std::setfill('0') << std::setw(2) << idx << ".png";
		cv::imwrite(stream.str(), camera_img);
	}
	cv::destroyAllWindows();

	return 0;
}