project(kurff)
 cmake_minimum_required(VERSION 3.10)
add_compile_options(-std=c++11)
include_directories(./)
add_executable(test_common test/test_common.cpp)
link_directories(/usr/local/lib)
add_library(fast SHARED proposals/fast/fast_9.cpp proposals/fast/fast_10.cpp proposals/fast/fast_11.cpp
            proposals/fast/fast_12.cpp proposals/fast/fast.cpp proposals/fast/nonmax.cpp)
add_executable(test_mser test/test_mser.cpp proposals/mser/mser.cpp utils/colors.cpp)
target_link_libraries(test_mser opencv_core opencv_highgui opencv_imgproc glog opencv_features2d fast)

