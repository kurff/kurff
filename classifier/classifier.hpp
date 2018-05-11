#ifndef __KURFF_CLASSIFIER_HPP__
#define __KURFF_CLASSIFIER_HPP__
#include "box.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;
#include <string>
using namespace std;
// recongize characters 
#include "core/registry.h"
namespace kurff{
    class Classifier{
        public:
            Classifier(){

            }
            ~Classifier(){

            }
        public:
            virtual bool initial(string model_def, string model) = 0;

            virtual void classify(const Mat& input, vector<Box>& boxes) = 0;


         

    };

    CAFFE_DECLARE_REGISTRY(ClassifierRegistry, Classifier);
    CAFFE_DEFINE_REGISTRY(ClassifierRegistry, Classifier);


    class CNNClassifier : public Classifier{
        public:
            CNNClassifier(){

            }
            ~CNNClassifier(){


            }

            bool initial(string model_def, string model){
                

                return true;
            }

            void classify(const Mat& input, vector<Box>& boxes){

                
            }
            

    };

    CAFFE_REGISTER_CLASS(ClassifierRegistry, CNNClassifier, CNNClassifier);








}



#endif