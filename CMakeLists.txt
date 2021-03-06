cmake_minimum_required(VERSION 3.0)
project(procam-calibration)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT DEFINED OpenCV_DIR)
    message(FATAL_ERROR "set OpenCV_DIR")
endif()

# OpenCV
find_package(OpenCV REQUIRED)

# header & source
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
file(GLOB CORE_SOURCES src/*.cpp)
file(GLOB CORE_HEADERS include/*.hpp)

# library
set(DEPENDENCY ${OpenCV_LIBS})

add_library(CORE STATIC ${CORE_HEADERS} ${CORE_SOURCES})
target_link_libraries(CORE ${DEPENDENCY})

# executable
add_executable(main_create_images main_create_images.cpp)
target_link_libraries(main_create_images CORE ${DEPENDENCY})

add_executable(main_take_images main_take_images.cpp)
target_link_libraries(main_take_images CORE ${DEPENDENCY})

add_executable(main_calibration main_calibration.cpp)
target_link_libraries(main_calibration CORE ${DEPENDENCY})