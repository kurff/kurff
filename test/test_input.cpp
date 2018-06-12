#include <memory>
#include "caffe/caffe.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace caffe;
using namespace std;
using namespace cv;

int main(){
    Caffe::set_mode(Caffe::GPU);
    std::shared_ptr<Net<float> > net;
    net.reset(new Net<float>("../script/test_input.prototxt", TEST));
    net->Reshape();
    net->Forward();
    Blob<float>* label = net->output_blobs()[0];
    //Blob<float>* label = net->output_blobs()[1];
    //label->mutable_data<>();
    cout<< label->num()<<" "<< label->channels()<<" "<< label->height()<<" "<<label->width()<<endl;
    for(int i = 0 ; i < label->num(); ++ i){
        Mat img = Mat::zeros(label->height(), label->width(), CV_8UC3);
        LOG(INFO)<<"create";
        
        for(int k = 0; k < label->height(); ++ k){
            for(int l = 0; l < label->width(); ++ l){
                for(int j = 0; j < label->channels(); ++ j){
                    //cout<<" "<<label->data_at(i,j,k,l);
                    int r = label->data_at(i,0,k,l);
                    int g = label->data_at(i,1,k,l);
                    int b = label->data_at(i,2,k,l);
                    img.at<Vec3b>(k,l) = Vec3b(b,g,r );
                }
                //cout<<endl;
            }
            //cout<<endl;
        }
        cv::imshow("image", img);
        cv::waitKey(0);
        //cout<<endl;
    }


    return 0;
}