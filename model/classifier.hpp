#ifndef __CLASSIFIER_HPP__
#define __CLASSIFIER_HPP__
#include "model/model.hpp"
#include "utils/utils.hpp"
#include "core/common.hpp"
#include "core/box.hpp"
#include "utils/visualization.hpp"
namespace kurff{
    //template<typename T>
    class Classifier : public Model{
        public:
            Classifier(int top_k) : Model(top_k){

            }
            ~Classifier(){

            }


            //template<typename T>
            void run(const Mat& image, vector<Box>& objects ){
                Mat sub;
                vector<float> confidence;
                vector<int> label;
                for(auto& obj : objects){
                    sub = image(Rect(obj.x, obj.y, obj.width, obj.height));
                    run_each(sub, confidence, label);
                    //LOG(INFO)<<"confidence: "<<confidence[0] <<" label: "<< label[0];
                    //cv::imshow("classifier", sub);
                    //cv::waitKey(0);
                    //obj.top_pred_.resize(this->top_k_);
                    //LOG(INFO)<<"top k"<< this->top_k_;
                    //int cnt = 0;
                    for(int i = 0; i < this->top_k_; ++ i ){
                        Top top;
                        top.confidence_ = confidence[i];
                        top.predict_ = label[i];
                        auto c = map_int2string.find(top.predict_);
                        top.name_ = c->second; 
                        obj.top_pred_.push_back(top);
                        
                    }
                    Mat img;
                    image.copyTo(img);
                    visualize(img, obj, Scalar(0,255,0), true);
                    cv::imshow("res", img);
                    cv::waitKey(0);

                }

                

            }
            
            void run_each(const Mat& image, vector<float>& confidence, vector<int>& label){
                Blob<float>* input_layer = this->net_->input_blobs()[0];
                input_layer->Reshape(1, this->num_channels_, this->input_geometry_.height, this->input_geometry_.width);
                this->net_->Reshape();
                std::vector<cv::Mat> input_channels;
                this->WrapInputLayer(&input_channels);
                this->Preprocess(image, &input_channels);
                this->net_->Forward();
                Blob<float>* output_layer = this->net_->output_blobs()[0];
                const float* begin = output_layer->cpu_data();
                const float* end = begin + output_layer->channels();
                vector<float> conf(begin, end);
                vector<int> index = sort_index(conf);

                confidence.clear();
                label.clear();
                for(int i = 0; i < this->top_k_; ++ i){
                    confidence.push_back(conf[index[i]]);
                    label.push_back(index[i]);
                }
            }

            
        protected:
            

        
    };
    CAFFE_REGISTER_CLASS(ModelRegistry, Classifier, Classifier);


}

#endif