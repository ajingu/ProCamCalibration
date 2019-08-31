#include "collect.hpp"

void collect_images(const std::string images_dir_path, std::vector<cv::Mat>& images)
{
	for (auto& p : directory_iterator(images_dir_path))
	{
		cv::Mat img = cv::imread(p.path().string());
		images.push_back(img);
		//imshow(p.path().string(), img);
	}
}