#ifndef __KURFF_VISUALIZATION_HPP__
#define __KURFF_VISUALIZATION_HPP__
#include "opencv2/opencv.hpp"
using namespace cv;
#include "glog/logging.h"
#include "data/annotation.hpp"
#include<string>
#include <vector>
using namespace std;
namespace kurff{
template<typename Box>
void visualize(Mat& img, const vector<Box>& boxes, Scalar scalar){
    LOG(INFO)<<"draw "<< boxes.size()<< " boxes";
    for(auto box : boxes){
                //LOG(INFO)<<i << "x: "<< result_.x0(i) <<" y: " <<result_.y0(i) ;
                //putText(img, std::to_string(i), cvPoint(result_.x0(i),result_.y0(i)-5), 
                //FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
        //LOG(INFO)<<"draw "<< box.x <<" "<< box.y;
        rectangle(img, box, scalar,3);
    }
}

template<typename Box>
void visualize(Mat& img, const vector<vector<Box> >& boxes, Scalar scalar ){
    LOG(INFO)<<"draw "<< boxes.size() <<" boxes";
    for(auto box : boxes){
        for(auto b : box){
            rectangle(img, b, scalar, 3);
        }
    }
}






}

#endif