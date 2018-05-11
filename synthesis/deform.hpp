#ifndef __DEFORM_HPP__
#define __DEFORM_HPP__
#include "opencv2/opencv.hpp"
#include "core/registry.h"
#include "core/parameters.hpp"
#include "utils/random.hpp"
using namespace cv;
namespace kurff{


    class Simulation{
        public:
            Simulation(Parameters* parameters){
                random_.reset(new Random());
            }
            ~Simulation(){

            }

            virtual void run(const Mat& input, Mat& output) = 0;
        protected:
            std::shared_ptr<Random> random_;

    };
    CAFFE_DECLARE_REGISTRY(SimulationRegistry, Simulation, Parameters*);
    CAFFE_DEFINE_REGISTRY(SimulationRegistry, Simulation, Parameters*);


    class Affine : public Simulation{
        public:
            Affine(Parameters* parameters): Simulation(parameters){
                angle_low_ = parameters->angle().lower();
                angle_up_ = parameters->angle().upper();
                scale_low_ = parameters->angle().lower();
                scale_up_ = parameters->angle().upper();
            }
            ~Affine(){

            }
        
            void run(const Mat& input, Mat& output){
                float r =  this->random_->NextDouble();
                float scale = scale_low_* r + (1-r)*scale_up_;
                float angle = angle_low_* r + (1-r)*angle_up_;
                
                
            }
        protected:
            cv::Mat trans_;
            float angle_low_;
            float angle_up_;
            float scale_low_;
            float scale_up_;
    };
    CAFFE_REGISTER_CLASS(SimulationRegistry, Affine, Affine);



    class Prospective : public Simulation{
        public:
            Prospective(Parameters* parameters): Simulation(parameters){

            }
            ~Prospective(){

            }
        
            void run(const Mat& input, Mat& output){

            }
        protected:
            cv::Mat trans_;


    };
    CAFFE_REGISTER_CLASS(SimulationRegistry, Prospective, Prospective);

    class Noise : public Simulation{
        public:
            Noise(Parameters* parameters) : Simulation(parameters), 
            mean_low_(parameters->mean().lower()), std_low_(parameters->std().lower()),
            mean_up_(parameters->mean().upper()), std_up_(parameters->std().upper()){
               
            }
            ~Noise(){

            }
            void run(const Mat& input, Mat& output){
                output = input.clone();
                float r =  this->random_->NextDouble();
                int mean = float(mean_low_)*r + (1-r)*float(mean_up_);
                int std = float(std_low_)*r +(1-r)*float(std_up_);
                cv::randn(output,mean,std);
            }
        protected:
            int mean_low_;
            int mean_up_;
            int std_low_;
            int std_up_;

    };
    CAFFE_REGISTER_CLASS(SimulationRegistry, Noise, Noise);

    class SubSample: public Simulation{
        public:
            SubSample(Parameters* parameters) : Simulation(parameters){

            }
            ~SubSample(){

            }

            void run(const Mat& input, Mat& output){
                float r = this->random_->NextDouble()/2.0f + 0.5f;
                Mat t;
                cv::resize(input, t, cv::Size(input.cols* r, input.rows*r));
                cv::resize(t, output, cv::Size(input.cols, input.rows));
            }
        protected:

    };
    CAFFE_REGISTER_CLASS(SimulationRegistry, SubSample, SubSample);


    // gamma changes
    class Illumination: public Simulation{
        public:
            Illumination(Parameters* parameters) : Simulation(parameters){
                gamma_lower_ = parameters->gamma().lower();
                gamma_upper_ = parameters->gamma().upper();
                lut_.reset(new uchar[256], std::default_delete<uchar [] >());

            }
            ~Illumination(){

            }
            void run(const Mat& input, Mat& output){
                float gamma = this->random_->NextDouble()/2.0f + 0.6f;
                
                for( int i = 0; i < 256; i++ ){  
                    lut_.get()[i] = saturate_cast<uchar>(pow((float)(i/255.0), gamma) * 255.0f);
                } 
                output = cv::Mat::zeros(cv::Size(input.cols, input.rows), CV_8UC3);
                for(int i = 0; i < input.rows; ++ i){
                    for(int j = 0; j < input.cols; ++ j){
                        Vec3b x = input.at<Vec3b>(i,j);
                        output.at<Vec3b>(i,j).val[0] = lut_.get()[x.val[0]];
                        output.at<Vec3b>(i,j).val[1] = lut_.get()[x.val[1]];
                        output.at<Vec3b>(i,j).val[2] = lut_.get()[x.val[2]];
                    }
                }
            }

        protected:
            float gamma_lower_;
            float gamma_upper_;
            std::shared_ptr<uchar> lut_;


    };

    CAFFE_REGISTER_CLASS(SimulationRegistry, Illumination, Illumination);

    class Background: public Simulation{
        public:
            Background(Parameters* parameters):Simulation(parameters){

            }
            ~Background(){

            }
            void run(const Mat& input, Mat& output){
                
            }

        protected:
            vector<string> background_name_;


    };
    CAFFE_REGISTER_CLASS(SimulationRegistry, Background, Background);


}
#endif