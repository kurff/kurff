#ifndef __KURFF_PROCESS_HPP__
#define __KURFF_PROCESS_HPP__


// process image 
// including denoise or
#include "core/registry.h"
#include "opencv2/opencv.hpp"
using namespace cv;
namespace kurff{
class Process{
    public:
        Process(){

        }
        ~Process(){

            
        }
        virtual void run(const cv::Mat & image, cv::Mat& output) = 0;
};

CAFFE_DECLARE_REGISTRY(ProcessRegistry, Process);
CAFFE_DEFINE_REGISTRY(ProcessRegistry, Process);

class ConnectComponent: public Process{
    public:
        ConnectComponent(){

        }
        ~ConnectComponent(){

        }
    
        void run(const cv::Mat & image, cv::Mat& output){
                    

        }
    protected:



};


CAFFE_REGISTER_CLASS(ProcessRegistry, ConnectComponent, ConnectComponent);

class Denoise : public Process{
    public:
        Denoise(){

        }
        ~Denoise(){

        }
        void run(const cv::Mat& image, cv::Mat& output, Size ksize){
            GaussianBlur(image, output,  ksize,  0.0);
        }
    protected:



};
CAFFE_REGISTER_CLASS(ProcessRegistry, Denoise, Denoise);






}




#endif