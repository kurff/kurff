#ifndef __SYNTHESIS_HPP__
#define __SYNTHESIS_HPP__
#include "opencv2/opencv.hpp"
#include "font/fonts.hpp"
#include "font/simulation.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <string>
using namespace cv;
using namespace std;
namespace Beta{
    class Synthesis{
        public:
            Synthesis(string fonts_list_file, string path): fonts_list_file_(fonts_list_file),path_(path){
                height_ = 64;
                width_= 64;
                characters_="0123456789ABCDEFGHIJKLMNOPQRSTUYWXYZabcdefghijklmnopqrstuvwxyz";
                num_grid_ = 4;
                count_ = 0;
            }

            ~Synthesis(){
                

            }

            void init(){
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
            }


            void get_keypoints(Mat& image, vector<Point2f>& keypoints){
                vector<Point2f> cache;
                keypoints.clear();
                int step = height_ / num_grid_;
                for(int i = 0; i < num_grid_; ++ i){
                    cache.clear();
                    for(int j = 0; j < width_; ++ j){
                        if(image.at<uchar>(i*step,j) > 200){
                            Point2f point;
                            point.x = j;
                            point.y = i*step;
                            cache.push_back(point);
                        }
                    }
                    if(cache.size() >=2){
                        keypoints.push_back(cache[0]);
                        keypoints.push_back(cache[cache.size() - 1]);
                    }else{
                        keypoints.push_back(Point2f(0.0f,i*step));
                        keypoints.push_back(Point2f(float(width_), i*step));
                    }
                }

                for(int i = 0; i < num_grid_; ++ i){
                    cache.clear();
                    for(int j = 0; j < height_; ++ j){
                        if(image.at<uchar>(j,i*step)>200){
                            Point2f point;
                            point.x = i*step;
                            point.y = j;
                            cache.push_back(point);
                        }
                    }
                    if(cache.size() >=2){
                        keypoints.push_back(cache[0]);
                        keypoints.push_back(cache[cache.size() -1]);
                    }else{
                        keypoints.push_back(Point2f(i*step,0.0f));
                        keypoints.push_back(Point2f(i*step, float(height_)));
                    }
                }
            }


            void visualize_keypoints(const Mat& image, const vector<Point2f>& keypoints){
                Mat vis;
                cvtColor(image, vis, cv::COLOR_GRAY2BGR);
                for(int i = 0; i < keypoints.size(); ++ i){
                     //Point point(keypoints[i].x, keypoints[i].y);
                     circle( vis,keypoints[i],3,Scalar( 0, 0, 255 ),2);
                }

                imshow("keypoints", vis);
                waitKey(0);
            }

            void save_image_keypoints(const Mat& image, const vector<Point2f>& keypoints, int index){

                imwrite(path_+"/images/"+characters_[index]+"_"+std::to_string(count_)+".png", image);

                ofstream fo(path_+"/keypoints/"+characters_[index]+"_"+std::to_string(count_)+".txt", ios::out);

                for(int i = 0; i < keypoints.size(); ++ i){
                    fo<< keypoints[i].x <<" "<< keypoints[i].y<<endl;
                }

                fo.close();
            }



            void run( ){

                vector<Point2f> keypoints;
                for(int i = 0; i < fonts_.size(); ++i){
                    for(int j = 0; j < characters_.length(); ++ j){
                        ++ count_;
                        fonts_[i]->draw(characters_, j);
                        Mat image = fonts_[i]->get();
                        get_keypoints(image, keypoints);
                        //visualize_keypoints(image, keypoints);
                        save_image_keypoints(image, keypoints, j);

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
            string characters_;
            int num_grid_;
            string path_;
            int count_;



            

            



    };









}











#endif