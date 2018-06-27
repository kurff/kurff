#ifndef __KURFF_BOX_HPP__
#define __KURFF_BOX_HPP__

#include <vector>
#include <string>
#include "opencv2/opencv.hpp"
#include "glog/logging.h"
using namespace std;
namespace kurff{

class Top{
    public:
        Top(const Top& top){
            confidence_ = top.confidence_;
            name_ = top.name_;
            predict_ = top.predict_;
        }
        Top():confidence_(0.0f), name_(""), predict_(0){

        }


    float confidence_;
    string name_;
    int predict_;
};


class Box: public cv::Rect{
    public:
        Box():cv::Rect(0,0,0,0){
            

        }
        ~Box(){

        }

        

        Box(const Box& box){
            x = box.x;
            y = box.y;
            height = box.height;
            width = box.width;
            top_pred_ = box.top_pred_;
            label_ = box.label_;
            label_name_ = box.label_name_;
        }

        bool check(int rheight, int rwidth){
            if(x < 0 || y <0 || width < 0 || height < 0 ){
                return false;
            }

            x = std::max(0,x);
            y = std::max(0,y);

            int x1 = std::min( x + width, rwidth-1);
            int y1 = std::min( y + height, rheight-1);

            width = x1 - x;
            height = y1 - y; 
            //LOG(INFO)<<x<<" "<<y<<" "<<width<<" "<<height;
            if(width <= 1 || height <= 1 ){
                return false;
            }else{
                return true;
            }

        }

    public:
        vector<Top> top_pred_;      //prediction
        vector<int> label_;         //label
        vector<string> label_name_; //label
        vector<float> dx_pred_;
        vector<float> dx_label_;
        

};












}







#endif