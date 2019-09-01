#include "const.hpp"
#include "graycode_pattern.hpp"

using namespace procam_calib;

int main()
{
	GrayCodePattern pattern = GrayCodePattern(GRAYCODE_WIDTH, GRAYCODE_HEIGHT);
	
	std::cout << "Press 's' key to start creating patterns";
	
	char key;
	while (true)
	{
		std::cin >> key;
		if (key == 's') break;
	}

	pattern.create(PATTERNS_DIR_PATH);

	return 0;
}