#ifndef __SYNTHESIS_HPP__
#define __SYNTHESIS_HPP__
#include "opencv2/opencv.hpp"
#include "synthesis/fonts.hpp"
#include "core/parameters.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include ""
using namespace cv;
using namespace std;
namespace kurff{
    template<typename T>
    class Synthesis{
        public:
            Synthesis(string fonts_list_file, string path): fonts_list_file_(fonts_list_file),path_(path){
                height_ = 64;
                width_= 64;
                count_ = 0;
                
            }

            ~Synthesis(){
                

            }

            void init(Parameters* parameters){
                ifstream fin(fonts_list_file_.c_str(), ios::in);
                string file;
                fonts_type_.clear();
                while(fin >> file){
                    fonts_type_.push_back(file);
                }

                int number = fonts_type_.size();
                fonts_.resize(number);
                for(int i = 0; i < number; ++ i){
                    fonts_[i] = new Fonts(height_, width_);
                    fonts_[i]->init(fonts_type_[i]);
                }
                transform_.clear();
                for(int i = 0; i < parameters->transform_size(); ++ i){
                    std::shared_ptr<T> ptr ( SimulationRegistry->Create( parameters->transform(i), parameters) );
                    transform_.push_back(ptr);
                }
            }

            void run( ){
                vector<Point2f> keypoints;
                for(int i = 0; i < fonts_.size(); ++i){
                    for(int j = 0; j < characters_.length(); ++ j){
                        ++ count_;
                        fonts_[i]->draw(characters_, j);
                        Mat image = fonts_[i]->get();
                        cv::imshow("src", image);
                        //visualize_keypoints(image, keypoints);
                        

                    }
                }

            }

            void destroy(){
                for(int i= 0; i < fonts_.size(); ++ i){
                    delete fonts_[i];
                }
            }

        protected:
            vector<Fonts*> fonts_;
            vector<string> fonts_type_;
            string fonts_list_file_;
            shared_ptr<Simulation> sim_;
            int height_;
            int width_;
            string path_;
            int count_;
            vector<std::shared_ptr<T> > transform_;
            
    };









}











#endif