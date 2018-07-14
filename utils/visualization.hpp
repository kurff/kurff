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

void visualize(Mat& img, const vector<Box>& boxes, Scalar scalar, bool show_text){
    for(auto box : boxes){
        if(show_text){
            //LOG(INFO)<<"show text: "<< box.top_pred_.size();
            for(auto top : box.top_pred_ ){
                //LOG(INFO)<<"show text";
                //if(top.name_ != "neg")
                if(top.predict_ != 62)
                putText(img, top.name_, cvPoint(box.x-5, box.y-5), FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,0,250), 2, CV_AA);
                
                
            }

        }

        //if(box.top_pred_[0].predict_ != 62){
            rectangle(img, box, scalar,3);
       // }


    }
}

void visualize(Mat& img, const Box& box, Scalar scalar, bool show_text){

    if(show_text){
        //LOG(INFO)<<"show text: "<< box.top_pred_.size();
        for(auto top : box.top_pred_ ){
                //LOG(INFO)<<"show text";
            putText(img, top.name_, cvPoint(box.x-5, box.y-5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,250), 2, CV_AA);
        }

    }
    rectangle(img, box, scalar,3);
    
}


void visualize(Mat& img, const vector<vector<Box> >& boxes, Scalar scalar ){
    LOG(INFO)<<"draw "<< boxes.size() <<" boxes";
    for(auto box : boxes){
        for(auto b : box){
            rectangle(img, b, scalar, 3);
        }
    }
}

void visualize_sub(Mat& img, const Box& box){
    cv::Mat sub = img(box);
    cv::imshow("src", sub);
    cv::waitKey(0);
}






}

#endif