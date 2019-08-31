#include "graycode_pattern.hpp"

const int PROJ_WIDTH = 1280;
const int PROJ_HEIGHT = 800;
const std::string SAVE_DIRECTORY_PATH = "../data/pattern";

using namespace procam_calib;

int main()
{
	GrayCodePattern pattern = GrayCodePattern(PROJ_WIDTH, PROJ_HEIGHT);
	
	std::cout << "Press 's' key to start creating patterns";
	
	char key;
	while (true)
	{
		std::cin >> key;
		if (key == 's') break;
	}

	pattern.create(SAVE_DIRECTORY_PATH);

	return 0;
}