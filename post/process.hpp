#ifndef __KURFF_PROCESS_HPP__
#define __KURFF_PROCESS_HPP__

#include "opencv2/opencv.hpp"
using namespace cv;
namespace kurff{
class Process{
    public:
        Process(){

        }
        ~Process(){

            
        }
        virtual void run(const cv::Mat & image) = 0;
};

class ConnectComponent: public Process{
    public:
        ConnectComponent(){

        }
        ~ConnectComponent(){

        }
    
        void run(const cv::Mat & image){
                    

        }
    protected:



};





}




#endif