#ifndef __SYNTHESIS_HPP__
#define __SYNTHESIS_HPP__
#include "opencv2/opencv.hpp"
#include "synthesis/fonts.hpp"
#include "core/parameters.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "synthesis/deform.hpp"
#include "core/common.hpp"
using namespace cv;
using namespace std;
namespace kurff{
    class Synthesis{
        public:
            Synthesis(string fonts_list_file): fonts_list_file_(fonts_list_file), max_count_(40000){
                //height_ = 64;
                //width_= 64;
                count_ = 0;
                
            }

            ~Synthesis(){
                

            }

            void init(Parameters* parameters){
                height_ = parameters->height();
                width_ = parameters->width();
                ifstream fin(fonts_list_file_.c_str(), ios::in);
                string file;
                fonts_type_.clear();
                while(fin >> file){
                    fonts_type_.push_back(file);
                }
                fin.close();
                LOG(INFO)<<"found "<< fonts_type_.size()<<" font file ttf";
                int number = fonts_type_.size();
                fonts_.clear();
                for(int i = 0; i < number; ++ i){
                    shared_ptr<Fonts> p (new Fonts(height_, width_));
                    fonts_.push_back(p);
                    p->init(fonts_type_[i]);
                    LOG(INFO)<<"initialize "<<i <<" "<< fonts_type_[i];
                }
                LOG(INFO)<<"initialize ttf done";
                transform_.clear();
                for(int i = 0; i < parameters->transform_size(); ++ i){
                    LOG(INFO)<< "creating "<<parameters->transform(i);
                    std::shared_ptr<Simulation> ptr = SimulationRegistry()->Create(parameters->transform(i), parameters);
                    transform_.push_back(ptr);
                }
            }

            void run(string file, string folder, int iter){
                std::ofstream f(file.c_str(), ios::out);
                vector<Point2f> keypoints;
                
                for(int it = 0; it < iter; ++ it ){
                    for(int i = 0; i < fonts_.size(); ++i){
                        LOG(INFO)<<fonts_type_[i] <<" count "<< count_ <<".png";
                        for(auto character : map_int2string ){                 
                        //LOG(INFO)<< character.second;
                            ++ count_;
                            fonts_[i]->draw(character.second, 0);
                            Mat image = fonts_[i]->get();
                            //cv::imshow("src", image);
                            image.copyTo(mask_);
                            Mat output;
                            run_transform(image, output);
                            cv::imshow("src", output);
                            cv::imwrite(folder+"/"+std::to_string(count_)+".png", output);
                            f << std::to_string(count_)+".png"<<" "<<character.first<<std::endl;

                            //visualize_keypoints(image, keypoints);
                            cv::waitKey(1);

                        }
                    }

                }

                f.close();
            }


            void run_transform(const cv::Mat& image, cv::Mat& output){

                image.copyTo(output);
                cv::Mat temp;
                image.copyTo(temp);
                for(auto trans : transform_){
                    trans->run(output, temp);
                    temp.copyTo(output);
                }

            }

            cv::Mat mask(){return mask_;}

        protected:
            vector<std::shared_ptr<Fonts> > fonts_;
            vector<string> fonts_type_;
            string fonts_list_file_;
            int height_;
            int width_;
            int count_;
            cv::Mat mask_;
            vector<std::shared_ptr<Simulation> > transform_;
            int max_count_;
            int iter_;
            
    };









}











#endif