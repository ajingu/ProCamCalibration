#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/structured_light.hpp>
#include "structured_light_pattern.hpp"

namespace procam_calib
{
	class GrayCodePattern : public StructuredLightPattern
	{
	private:
		int proj_width;
		int proj_height;

	public:
		GrayCodePattern(int proj_width, int proj_height);
		void create(std::string save_directory_path) override;
	};
}