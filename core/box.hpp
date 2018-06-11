#ifndef __KURFF_BOX_HPP__
#define __KURFF_BOX_HPP__

#include <vector>
#include <string>
#include "opencv2/opencv.hpp"
using namespace std;
namespace kurff{

typedef struct Top_{
    float confidence_;
    string name_;
    int predict_;
}Top;


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
            
        }
    public:
        vector<Top> top_pred_;      //prediction
        vector<int> label_;         //label
        vector<string> label_name_; //label

};












}







#endif