#pragma once

namespace procam_calib
{
	class StructuredLightPattern
	{
	public:
		virtual void create(std::string save_directory_path) = 0;
	};
}