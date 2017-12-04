#ifndef __KURFF_CHARACTER_HPP__
#define __KURFF_CHARACTER_HPP__
#include <vector>
#include "opencv2/opencv.hpp"
#include <memory>
#include "glog/logging.h"
using namespace cv;
using namespace std;

#include "box.hpp"
namespace kurff{
class Character{
    public:
        Character(){

        }

        ~Character(){


        }

        virtual void proposals(const Mat& input){

        }
        vector<Box> get_boxes() const {
            return boxes_;
        }
        size_t get_number() const {
            return boxes_.size();
        }
        int x0(size_t idx) const {
            return boxes_[idx].x0_;
        }
        int y0(size_t idx)const {
            return boxes_[idx].y0_;
        }
        int h(size_t idx)const {
            return boxes_[idx].h_;
        }
        int w(size_t idx)const {
            return boxes_[idx].w_;
        }

    protected:
        vector<Box> boxes_;
};

class YoloCharacter: public Character{
    public:
        YoloCharacter(){

        }

        ~YoloCharacter(){


        }

        void proposals(const Mat& input){


        } 
    private:


};

class SSDCharacter: public Character{
    public:
        SSDCharacter(){

        }

        ~SSDCharacter(){

        }

        void proposals(const Mat& input){

        }
        
};



} // end of namespace kurff

#endif