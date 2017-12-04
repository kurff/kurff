#ifndef __KURFF_VISUALIZATION_HPP__
#define __KURFF_VISUALIZATION_HPP__
#include "opencv2/opencv.hpp"
using namespace cv;
#include "glog/logging.h"
#include<string>

namespace kurff{
template<typename Result>
class Visualization{
    public:
        Visualization(const Result& result):result_(result){


        }
        ~Visualization(){

        }

    public:
        const Result result_;

        void visualize(Mat& img, Scalar scalar){
            LOG(INFO)<<result_.get_number();
            for(int i = 0; i < result_.get_number(); ++i){
                //LOG(INFO)<<i << "x: "<< result_.x0(i) <<" y: " <<result_.y0(i) ;
                putText(img, std::to_string(i), cvPoint(result_.x0(i),result_.y0(i)-5), 
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
                rectangle(img, Rect(result_.x0(i),result_.y0(i),result_.w(i),result_.h(i)), scalar,3);
            }
        }
};

template<typename Result>
class TextVisual{
    public:
        TextVisual(const Result& result):result_(result){

        }
        ~TextVisual(){


        }
    public:
        const Result result_;
        void visualize(Mat& img, Scalar scalar){
            LOG(INFO)<<result_.get_text_number();
            for(int i = 0; i < 100;/*result_.get_text_number();*/ ++i){
                //LOG(INFO)<<i << "x: "<< result_.x0(i) <<" y: " <<result_.y0(i) ;
                putText(img, std::to_string(result_.f(i)), cvPoint(result_.c0(i),result_.r0(i)-5), 
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,0), 1, CV_AA);
                rectangle(img, Rect(result_.c0(i),result_.r0(i),result_.w0(i),result_.h0(i)), scalar,3);
            }
        }



};


}

#endif