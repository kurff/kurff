#ifndef __CLASSIFIER_HPP__
#define __CLASSIFIER_HPP__
#include "model/model.hpp"
#include "utils/utils.hpp"
#include "core/common.hpp"
#include "core/box.hpp"
namespace kurff{
    template<typename T>
    class Classifier : public Model<T>{
        public:
            Classifier(int top_k) : Model<T>(top_k){

            }
            ~Classifier(){

            }


            void run(const Mat& image, vector<T>& objects ){
                Mat sub;
                vector<float> confidence;
                vector<int> label;
                for(auto& obj : objects){
                    sub = image(Rect(obj.x, obj.y, obj.width, obj.height));
                    run_each(sub, confidence, label);
                    obj.top_pred_.resize(this->top_k_);
                    int cnt = 0;
                    for(auto & top : obj.top_pred_ ){
                        top.confidence_ = confidence[cnt];
                        top.predict_ = label[cnt];
                        auto c = map_int2string.find(top.predict_);
                        top.name_ = c->second; 
                        ++ cnt; 
                    }
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
                vector<size_t> index = sort_index(conf);

                confidence.clear();
                label.clear();
                for(int i = 0; i < this->top_k_; ++ i){
                    confidence.push_back(conf[index[i]]);
                    label.push_back(index[i]);
                }
            }

            
        protected:
            

        
    };
    CAFFE_REGISTER_CLASS(ModelRegistry, Classifier<Box>, Classifier<Box>);


}

#endif