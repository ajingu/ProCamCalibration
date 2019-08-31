#include "graycode_pattern.hpp"

namespace procam_calib
{
	GrayCodePattern::GrayCodePattern(int proj_width, int proj_height) : proj_width(proj_width), proj_height(proj_height){}

	void GrayCodePattern::create(std::string save_directory_path)
	{
		cv::structured_light::GrayCodePattern::Params params;
		params.width = proj_width;
		params.height = proj_height;

		std::vector<cv::Mat> patterns;
		cv::Mat black, white;

		cv::Ptr<cv::structured_light::GrayCodePattern> graycode = cv::structured_light::GrayCodePattern::create(params);
		graycode->generate(patterns);
		graycode->getImagesForShadowMasks(black, white);
		patterns.push_back(white);
		patterns.push_back(black);

		for (int idx = 0; idx < patterns.size(); idx++)
		{
			cv::imshow("show", patterns[idx]);
			cv::waitKey(30);

			std::ostringstream image_path;
			image_path << save_directory_path << "/image";
			if (idx < 10)
			{
				image_path << "0";
			}
			image_path << std::to_string(idx) << ".png";

			cv::imwrite(image_path.str(), patterns[idx]);
		}
	}
}