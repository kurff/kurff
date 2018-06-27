#ifndef __ANOTATION_HPP__
#define __ANOTATION_HPP__
#include "core/registry.h"
#include <vector>
#include <string>
#include <fstream>
#include "glog/logging.h"
#include "utils/utils.hpp"
#include "core/box.hpp"
#include "core/common.hpp"
using namespace std;
namespace kurff{
    class Annotation{
        public:
            Annotation(){

            }
            ~Annotation(){

            }

            virtual void load(string file_name, vector<vector<Box> >& boxes) = 0;

        protected:

            
        


    };


    CAFFE_DECLARE_REGISTRY(AnnotationRegistry, Annotation);
    CAFFE_DEFINE_REGISTRY(AnnotationRegistry, Annotation);

    
    class ICDAR2013Annotation : public Annotation{
        public:
            ICDAR2013Annotation(){


            }
            ~ICDAR2013Annotation(){

            }

            void load(string file_name, vector<vector<Box> >& boxes_all){
                ifstream fc(file_name, ios::in);
                if(!fc.is_open()){
                    LOG(INFO) <<"can not open anotation file"<< file_name;
                    return;
                }

                string text_content;
                boxes_all.clear();
                vector<Box> boxes;
                Box box;
                int x1 = 0, y1 = 0;
                while(getline(fc, text_content)){
                    vector<string> names;
                    SplitString(text_content, names, " ");
                    box.label_name_.clear();
                    if(names[0][0]=='#'){
                        //LOG(INFO)<<"error";
                        LOG(INFO)<<text_content;
                        continue;
                    }
                    if(names.size()<=1){
                        boxes_all.push_back(boxes);
                        boxes.clear();
                    }else{
                        stringstream ss;
                        ss << names[5];
                        ss >> box.x;
                        ss.clear();
                        ss << names[6];
                        ss >> box.y;
                        ss.clear();
                        ss << names[7];
                        ss >> x1;
                        box.width =x1-box.x;
                        ss.clear();
                        ss << names[8];
                        ss >> y1;
                        box.height = y1-box.y;
                        

                        box.label_name_.push_back (names[9].substr(1,1));
                        auto it = map_string2int.find(box.label_name_[0]);
                        if(it != map_string2int.end()){
                            box.label_.push_back(it->second);
                        }else{
                            box.label_.push_back(map_string2int.size()-1);
                        }
                        
                        //LOG(INFO)<<names[9] <<" "<< text_content;
                        //LOG(INFO)<< box.label_name_[0];
                        boxes.push_back(box);
                    }
                }
                boxes_all.push_back(boxes);
                fc.close();
            }



        protected:
            
    };

    CAFFE_REGISTER_CLASS(AnnotationRegistry, ICDAR2013Annotation, ICDAR2013Annotation);


    class ReadDetectionResult : public Annotation{
        public:
            ReadDetectionResult(){

            }
            ~ReadDetectionResult(){

            }

            void load(string file_name, vector<vector<Box> >& boxes){
                


            }

    };
    
}

#endif