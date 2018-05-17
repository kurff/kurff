#ifndef __KURFF_CLASSIFIER_HPP__
#define __KURFF_CLASSIFIER_HPP__
#include "core/box.hpp"
#include "opencv2/opencv.hpp"

#include <string>
#include "classifier/network.hpp"
#include "core/registry.h"
#include "core/common.hpp"
#include "caffe2/core/net.h"
#include <memory>
using namespace std;
using namespace cv;
// recongize characters 

namespace kurff{

    template<typename DataContext>
    class Classifier{
        public:
            Classifier(){

            }
            ~Classifier(){

            }
        public:
            virtual bool initial(string model_def, string model) = 0;

            virtual bool build() = 0;

            virtual void classify(const Mat& input, vector<Box>& boxes) = 0;


         

    };

    CAFFE_DECLARE_REGISTRY(ClassifierRegistry, Classifier<CPUContext>);
    CAFFE_DEFINE_REGISTRY(ClassifierRegistry, Classifier<CPUContext>);


    template<typename DataContext>
    class CNNClassifier : public Classifier<DataContext>{
        public:
            CNNClassifier(): Classifier<DataContext>(){

            }
            ~CNNClassifier(){


            }

            bool initial(string model_def, string model){

                network_.reset(new Network<DataContext>());

                return true;
            }

            bool build(){
                int number_class = map_int2string.size();
                std::map<string, vector<int> > inputs{{"data",{32,64,64,3}}};
                std::map<string, vector<int> > outputs{{"class",{number_class}}};
                std::map<string, vector<int> > labels{{"label",{number_class}}};
                bool training = true;
                network_.reset(new Network<DataContext>(inputs, outputs, labels, training));
                caffe2::NetDef init_model;
                caffe2::NetDef predict_model;
                caffe2::NetDef update_model;
                bool use_gpu = false;
                network_->init(init_model, predict_model, update_model);
                network_->create_network();
                network_->save("classifier");
                network_->allocate();
                network_->init_parameters();
                return true;
            }

            void classify(const Mat& input, vector<Box>& boxes){

                
            }
        protected:
            std::shared_ptr<Network<DataContext> > network_;


    };

    CAFFE_REGISTER_CLASS(ClassifierRegistry, CNNClassifier<CPUContext>, CNNClassifier<CPUContext>);








}



#endif