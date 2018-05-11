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

            }
            ~Illumination(){

            }
            void run(const Mat& input, Mat& output){
                //cv::illuminationChange
            }
            
        protected:
            


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