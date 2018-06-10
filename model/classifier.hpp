#ifndef __CLASSIFIER_HPP__
#define __CLASSIFIER_HPP__
#include "model/model.hpp"
namespace kurff{
    template<typename T>
    class Classifier : public Model<T>{
        public:
            Classifier() : Model<T>(){

            }
            ~Classifier(){

            }


            void run(const Mat& image, vector<T>& objects ){
                Blob<float>* input_layer = net_->input_blobs()[0];
                input_layer->Reshape(1, num_channels_, input_geometry_.height, input_geometry_.width);
                net_->Reshape();
                std::vector<cv::Mat> input_channels;
                WrapInputLayer(&input_channels);
                Preprocess(image, &input_channels);
                net_->Forward();
                

            }
            
            void run_each(const Mat& image, vector<float>& confidence, vector<int>& label){
                Blob<float>* input_layer = net_->input_blobs()[0];
                input_layer->Reshape(1, num_channels_, input_geometry_.height, input_geometry_.width);
                net_->Reshape();
                std::vector<cv::Mat> input_channels;
                WrapInputLayer(&input_channels);
                Preprocess(image, &input_channels);
                net_->Forward();




            }

            
        protected:

        
    };

}

#endif