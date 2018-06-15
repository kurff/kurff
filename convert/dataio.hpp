#ifndef __DATA_IO_HPP__
#define __DATA_IO_HPP__

#include "caffe/utils/io.hpp"
#include "opencv2/opencv.hpp"
#include "core/box.hpp"
#include "caffe/proto/caffe.pb.h"
#include <string>
using namespace cv;
using namespace caffe;
using namespace std;

namespace kurff{

    // read memory to datum
    bool ReadMemoryToDatum(cv::Mat& image, const Box& box, int resize_height, int resize_width, Datum& datum){
        int height = image.rows;
        int width = image.cols;
        cv::Mat sub = image(Rect(box.x,box.y,box.width,box.height));
        cv::Mat img;
        cv::resize(sub,img,Size(resize_width,resize_height));
        CVMatToDatum(img, datum);
        return true;
    }
    bool ReadImageToDatum(const string& file, Datum& datum){
        

    }






}

#endif