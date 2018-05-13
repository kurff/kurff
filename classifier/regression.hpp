#ifndef __REGRESSION_HPP__
#define __REGRESSION_HPP__

#include <string>
#include <vector>
#include "core/box.hpp"
#include "opencv2/opencv.hpp"
#include "core/registry.h"
using namespace std;
using namespace cv;

namespace kurff{
    template<typename DataContext>
    class Regression{
        public:
            Regression(){

            }
            ~Regression(){

            }
            virtual bool initial(string model_def, string model) = 0;

            virtual bool build() = 0;

            virtual void classify(const Mat& input, const vector<Box>& previous, vector<Box>& current) = 0;

        protected:



    };

    CAFFE_DECLARE_REGISTRY(RegressionRegistry, Regression);
    CAFFE_DEFINE_REGISTRY(RegressionRegistry, Regression);

    template<typename DataContext>
    class CNNRegression : public Regression<DataContext>{
        public:
            CNNRegression() : Regression<DataContext>(){

            }
            ~CNNRegression(){

            }

            bool initial(string model_def, string model){
                
                return true;

            }

            bool build(){

                return true;
            }

            void classify(const Mat& input, const vector<Box>& previous, vector<Box>& current){


            }
         
        protected:

    };



}

#endif