#ifndef __DATA_HPP__
#define __DATA_HPP__
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "core/registry.h"
using namespace cv;
using namespace std;

namespace kurff{
    class DataReader{
        public:
            DataReader(){

            }
            ~DataReader(){

            }

            virtual void load(string file_name) = 0;

        protected:



            



    };

    CAFFE_DECLARE_REGISTRY(DataReaderRegistry, DataReader);
    CAFFE_DEFINE_REGISTRY(DataReaderRegistry, DataReader);

    class ICDAR2013DataReader : public DataReader{
        public:
            ICDAR2013DataReader(){

            }
            ~ICDAR2013DataReader(){

            }

            void load(string file_name){
                image_ = imread(file_name);

            }
        protected:
            cv::Mat image_;

    };

    CAFFE_REGISTER_CLASS(DataReaderRegistry, ICDAR2013DataReader, ICDAR2013DataReader);


}




#endif