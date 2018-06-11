project(kurff)
 cmake_minimum_required(VERSION 3.5)
add_compile_options(-std=c++11)
include_directories(./)
include_directories(/usr/include/freetype2/)
include_directories(/usr/local/include)
include_directories(3rdparty/caffe/distribute/include)
include_directories(/usr/local/cuda/include)

link_directories(/usr/local/cuda/lib64)
link_directories(3rdparty/caffe/distribute/lib)
link_directories(/usr/local/lib)
link_directories(/usr/lib/x86_64-linux-gnu/)
add_library(fast SHARED proposals/fast/fast_9.cpp proposals/fast/fast_10.cpp proposals/fast/fast_11.cpp
            proposals/fast/fast_12.cpp proposals/fast/fast.cpp proposals/fast/nonmax.cpp)
add_executable(test_mser test/test_mser.cpp proposals/mser/mser.cpp utils/colors.cpp)
target_link_libraries(test_mser opencv_core opencv_highgui opencv_imgproc glog opencv_features2d fast opencv_imgcodecs )#opencv_imgcodecs

add_executable(test_common test/test_common.cpp proto/kurff.pb.cc)
target_link_libraries(test_common protobuf glog opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)

add_subdirectory(3rdparty)

add_executable(main main.cpp proto/kurff.pb.cc)
target_link_libraries(main protobuf glog)

add_executable(test_synthesis test/test_synthesis.cpp proto/kurff.pb.cc)
target_link_libraries(test_synthesis protobuf glog opencv_imgcodecs opencv_core opencv_highgui opencv_imgproc  freetype) 

add_executable(test_dataset test/test_dataset.cpp proposals/mser/mser.cpp utils/colors.cpp)
target_link_libraries(test_dataset glog opencv_core opencv_highgui opencv_imgproc fast opencv_imgcodecs)
#add_executable(test_network test/test_network.cpp classifier/net.cc)
#target_link_libraries(test_network caffe2 caffe2_protos opencv_core opencv_highgui opencv_imgproc  glog)


add_executable(test_video_canny test/test_video_canny.cpp proposals/mser/mser.cpp utils/colors.cpp)
target_link_libraries(test_video_canny glog opencv_core opencv_videoio opencv_highgui opencv_imgproc fast opencv_imgcodecs)

add_executable(convert_database utils/convert_database.cpp)
target_link_libraries(convert_database caffe boost_system boost_filesystem opencv_core opencv_highgui opencv_imgcodecs opencv_imgproc  glog gflags )

add_executable(test_classifier test/test_classifier.cpp)
target_link_libraries(test_classifier caffe boost_system boost_filesystem opencv_core opencv_highgui opencv_imgcodecs opencv_imgproc  glog gflags)