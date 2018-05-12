project(kurff)
 cmake_minimum_required(VERSION 3.5)
add_compile_options(-std=c++11)
include_directories(./)
include_directories(/usr/include/freetype2/)
add_executable(test_common test/test_common.cpp proto/kurff.pb.cc)
target_link_libraries(test_common protobuf glog opencv_core opencv_highgui opencv_imgproc)
link_directories(/usr/local/lib)
link_directories(/usr/lib/x86_64-linux-gnu/)
add_library(fast SHARED proposals/fast/fast_9.cpp proposals/fast/fast_10.cpp proposals/fast/fast_11.cpp
            proposals/fast/fast_12.cpp proposals/fast/fast.cpp proposals/fast/nonmax.cpp)
add_executable(test_mser test/test_mser.cpp proposals/mser/mser.cpp utils/colors.cpp)
target_link_libraries(test_mser opencv_core opencv_highgui opencv_imgproc glog opencv_features2d fast )#opencv_imgcodecs

add_executable(main main.cpp proto/kurff.pb.cc)
target_link_libraries(main protobuf glog)

add_executable(test_synthesis test/test_synthesis.cpp proto/kurff.pb.cc)
target_link_libraries(test_synthesis protobuf glog opencv_core opencv_highgui opencv_imgproc freetype) 