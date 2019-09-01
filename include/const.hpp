#pragma once

#include <iostream>

const std::string PATTERNS_DIR_PATH = "../data/pattern";
const std::string CAMERA_DIR_PATH = "../data/camera";
const std::string CORRESPONDENCE_C2P_X_PATH = "../data/correspondence/c2p_x.xml";
const std::string CORRESPONDENCE_C2P_Y_PATH = "../data/correspondence/c2p_y.xml";
const std::string CORRESPONDENCE_IMG_PATH = "../data/correspondence/c2p.png";
const std::string PATTERN_WINDOW_NAME = "Pattern";
const std::string CAMERA_WINDOW_NAME = "Camera";
const int PROJ_WIDTH = 1280;
const int PROJ_HEIGHT = 800;
const int WIDTH_STEP = 4;
const int HEIGHT_STEP = 4;
const int GRAYCODE_WIDTH = PROJ_WIDTH/WIDTH_STEP;
const int GRAYCODE_HEIGHT = PROJ_HEIGHT/HEIGHT_STEP;
const int CAM_WIDTH = 1920;
const int CAM_HEIGHT = 1080;
const int PROJ_SCREEN_POS_X = 1920;
const int PROJ_SCREEN_POS_Y = 0;
const int THRESH = 10;
