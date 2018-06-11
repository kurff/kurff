#include "utils/utils.hpp"
#include "core/box.hpp"
#include "model/model.hpp"
#include "model/classifier.hpp"
#include "opencv2/opencv.hpp"
#include "core/common.hpp"
#include <iostream>
using namespace cv;
using namespace std;
using namespace kurff;
int main(){
    // vector<float> confidence{0.1,0.2,0.5,0.1,0.9,0.5};
    // vector<size_t> index = sort_index(confidence);
    // for(int i = 0; i < confidence.size(); ++ i){
    //     std::cout<<" "<<confidence[i];
    // }
    // std::cout<<endl;
    // for(int i = 0; i < confidence.size(); ++ i){
    //     std::cout<<" "<<confidence[index[i]];
    // }

    int top_k = 5;
    std::shared_ptr<Model<Box> > model = ModelRegistry()->Create("Classifier", top_k);
    model->init("../script/deploy.prototxt","../build/classifier__iter_599.caffemodel",1);

    cv::Mat img = cv::imread("images/1.png");
    vector<float> confidence;
    vector<int> label;
    //model->run_each(img, confidence, label);
    //for(int i = 0; i < top_k; ++ i){
    //    auto x = map_int2string.find(label[i]);
    //    cout<< "label: "<< label[i] <<" confidence: "<< confidence[i]<<" name: "<< x->second << std::endl;
   // }

}