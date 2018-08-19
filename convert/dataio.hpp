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


    void diff(const Box& box, const Box& gt, float& dx, float& dy, float &dw, float& dh){
        float d = sqrt( float(box.width)*float(box.width) + float(box.height)*float(box.height));
        dx = (float(gt.x) - float(box.x)) / d;
        dy = (float(gt.y) - float(box.y)) / d;
        
        dw = log(float(gt.width) / d);
        dh = log(float(gt.height) /  d);

    }

    // read memory to datum
    bool ReadMemoryToDatum(cv::Mat& image, Box& box, const Box& gt, float overlap, int resize_height, int resize_width, int label, Datum* datum){
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
        // cv::imshow("sub", img);
        // if(label != 0 ){
        //     cv::waitKey(0);
        // }else{
        //     cv::waitKey(1);
        // }

        CVMatToDatum(img, datum);
        datum->set_label(label);
        
        datum->mutable_float_data()->Clear();

        float dx = 0.0f, dy = 0.0f, dw = 0.0f, dh = 0.0f;
        diff(box, gt, dx, dy, dw, dh);
        
        LOG(INFO)<<"dx: "<< dx <<" dy: "<< dy<<" dw: "<< dw<<" dh: "<< dh <<" overlap: "<< overlap;
        LOG(INFO)<<"label: "<< label;
        if(label !=map_int2string.size() -1){
            datum->add_float_data(dx);
            datum->add_float_data(dy);
            datum->add_float_data(dw);
            datum->add_float_data(dh);
            datum->add_float_data(overlap);
        }else{
            datum->add_float_data(0.0f);
            datum->add_float_data(0.0f);
            datum->add_float_data(0.0f);
            datum->add_float_data(0.0f);
            datum->add_float_data(overlap);
        }
        return flag;
    }
    bool ReadBoxImageToDatum(const string& file, Datum* datum){
        

    }






}

#endif