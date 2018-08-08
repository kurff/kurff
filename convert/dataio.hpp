#ifndef __DATA_IO_HPP__
#define __DATA_IO_HPP__



#include "caffe/util/io.hpp"
#include "opencv2/opencv.hpp"
#include "core/box.hpp"
#include "caffe/proto/caffe.pb.h"
#include <string>
#include "glog/logging.h"
using namespace cv;
using namespace caffe;
using namespace std;



namespace kurff{

    // read memory to datum
    bool ReadMemoryToDatum(cv::Mat& image, Box& box, int resize_height, int resize_width, int label, Datum* datum){
        int height = image.rows;
        int width = image.cols;

        //box.x = std::max(box.x, 0);
        bool flag = box.check(height,width);
        assert(box.x+box.width < width);
        assert(box.y+box.height < height);
        if(flag == false){
            return flag;
        }
        //LOG(INFO)<<"(x,y,width,height) : "<<"("<<box.x<<","<<box.y<<","<<box.width<<","<<box.height<<")";
        cv::Mat sub = image(Rect(box.x,box.y,box.width,box.height));
        cv::Mat img;
        
        cv::resize(sub,img,Size(resize_width,resize_height));
        cv::imshow("src", img);
        cv::waitKey(0);
        CVMatToDatum(img, datum);
        datum->set_label(label);
        
        return flag;
    }
    bool ReadBoxImageToDatum(const string& file, Datum* datum){
        

    }






}

#endif