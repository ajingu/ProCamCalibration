#pragma once

#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std::experimental::filesystem;

void collect_images(const std::string images_dir_path, std::vector<cv::Mat>& images);