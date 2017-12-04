#ifndef __KURFF_UTILS_HPP_
#define __KURFF_UTILS_HPP_
#include "box.hpp"

namespace kurff{

float overlap(const Box& b0, const Box& b1){
    if(b0.y0_ > b1.y1_){
        return 0.0f;
    }
    if(b0.x0_ > b1.x1_){
        return 0.0f;
    }
    if(b0.y1_ < b1.y0_){
        return 0.0f;
    }
    if(b0.x1_ < b1.x0_){
        return 0.0f;
    }

    float x = min(b0.x1_,b1.x1_) - max(b0.x0_,b1.x0_);
    float y = min(b0.y1_,b1.y1_) - max(b0.y0_,b1.y0_);
    float intersection = x*y;
    float a0 = (b0.y1_-b0.y0_)*(b0.x1_-b0.x0_);
    float a1 = (b1.y1_-b1.y0_)*(b1.x1_-b1.x0_);
    return intersection /(a0+a1-intersection);
}


bool compare(const TextBox& t0, const TextBox& t1){
    return t0.confidence_ > t1.confidence_;
}

}







#endif

