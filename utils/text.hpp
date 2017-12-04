#ifndef __KURFF_TEXT_HPP__
#define __KURFF_TEXT_HPP__
#include "opencv2/opencv.hpp"
#include "box.hpp"
using namespace cv;
#include <vector>
using namespace std;
namespace kurff{
class Text{
    public:
        Text(){

        }

        ~Text(){


        }

        virtual void init() = 0 ; 
        virtual void proposals(const Mat& img) = 0 ; 
        virtual void release() = 0;


    private:
        vector<Box> texts_;


};


class CannyText: public Text{
    public:
        CannyText(){

        }
        ~CannyText(){

        }

        void init(int lowThreshold, int kernel_size){
            lowThreshold_ = lowThreshold;
            kernel_size_ = kernel_size;
        }
        void proposals(const Mat& img){
          

            






        }

        void release(){


        }



    private:
        int lowThreshold_;
        int kernel_size_;



};



class SSDText: public Text{
    public:
        SSDText(){

        }

        ~SSDText(){


        }

        void init(){

        }
        void proposals(const Mat& img){

        }
        void release(){

        }

    private:



};







}





#endif