#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/structured_light.hpp>
#include "collect.hpp"
#include "const.hpp"

int main()
{
	cv::structured_light::GrayCodePattern::Params params;
	params.width = GRAYCODE_WIDTH;
	params.height = GRAYCODE_HEIGHT;
	auto patterns = cv::structured_light::GrayCodePattern::create(params);

	std::vector<cv::Mat> camera_images;
	cv::Mat white, black;

	collect_images(CAMERA_DIR_PATH, camera_images);
	black = camera_images.back();
	camera_images.pop_back();
	white = camera_images.back();
	camera_images.pop_back();

	cv::cvtColor(black, black, cv::COLOR_BGR2GRAY);
	cv::cvtColor(white, white, cv::COLOR_BGR2GRAY);

	cv::Mat substract;
	cv::subtract(white, black, substract);
	cv::imshow("Substract", substract);
	cv::waitKey(0);
	//cv::destroyAllWindows();

	cv::Mat c2p_x = cv::Mat::zeros(CAM_HEIGHT, CAM_WIDTH, CV_16S);
	cv::Mat c2p_y = cv::Mat::zeros(CAM_HEIGHT, CAM_WIDTH, CV_16S);
	cv::Mat show = cv::Mat::zeros(CAM_HEIGHT, CAM_WIDTH, CV_8UC3);
	int valid_count = 0;
	for (int y = 0; y < CAM_HEIGHT; y++)
	{
		for (int x = 0; x < CAM_WIDTH; x++)
		{
			cv::Point proj_pixel;
			if((int)substract.at<cv::uint8_t>(y, x) > THRESH &&
				patterns->getProjPixel(camera_images, x, y, proj_pixel))
			{
				c2p_x.at<cv::int16_t>(y, x) = proj_pixel.x;
				c2p_y.at<cv::int16_t>(y, x) = proj_pixel.y;
				show.at<cv::Vec3b>(y, x)[0] = (float)proj_pixel.x / GRAYCODE_WIDTH * 255;
				show.at<cv::Vec3b>(y, x)[1] = (float)proj_pixel.y / GRAYCODE_HEIGHT * 255;
				valid_count++;
			}
			else
			{
				c2p_x.at<cv::int16_t>(y, x) = -1;
				c2p_y.at<cv::int16_t>(y, x) = -1;
			}
		}
	}
	std::cout << "Valid Rate: " << (float)valid_count / (CAM_HEIGHT*CAM_WIDTH) << std::endl;
    

	cv::FileStorage fs_c2p_x(CORRESPONDENCE_C2P_X_PATH, cv::FileStorage::WRITE);
	cv::FileStorage fs_c2p_y(CORRESPONDENCE_C2P_Y_PATH, cv::FileStorage::WRITE);
	fs_c2p_x << "c2p_x" << c2p_x;
	fs_c2p_y << "c2p_y" << c2p_y;
	fs_c2p_x.release();
	fs_c2p_y.release();


	cv::imshow("Correspondence", show);
	cv::imwrite(CORRESPONDENCE_IMG_PATH, show);
	cv::waitKey(0);

	return 0;
}