#ifndef __DATASET_HPP__
#define __DATASET_HPP__
#include "data/data.hpp"
#include "annotation.hpp"
#include <fstream>

#include <map>
using namespace std;
namespace kurff{
    class Dataset{
        public:
            Dataset(string image_path, string anno_path) : image_path_(image_path), anno_path_(anno_path){

            }

            ~Dataset(){

            }

            virtual void load(string file) = 0;
        protected:
            std::map<string, std::pair< string , string> > dataset_;
            std::unique_ptr<DataReader> data_reader_;
            std::unique_ptr<Annotation> anno_reader_;
            string image_path_;
            string anno_path_;
            vector<string> files_;
            std::map<string , vector<vector<Box> > > bounding_boxes_;

    };

    class ICDAR2013Dataset: public Dataset{
        public:
            ICDAR2013Dataset(string image_path, string anno_path):Dataset(image_path, anno_path){
                this->data_reader_ = DataReaderRegistry()->Create("ICDAR2013DataReader");
                this->anno_reader_ = AnnotationRegistry()->Create("ICDAR2013Annotation");
            }
            ~ICDAR2013Dataset(){

            }

            void load(string file){
                ifstream f(file, std::ios::in);
                string name;
                while(f >> name){
                    this->files_.push_back(name);
                    dataset_.insert(
                        std::make_pair( name, std::make_pair(image_path_+"/"+ name + ".jpg", anno_path_+"/"+name+"_GT.txt")));
                }
                f.close();
                //for(int i = 0; i < dataset_.size(); ++ i)
                for(auto d : dataset_ ){
                    this->anno_reader_->load(d.second.second);
                    bounding_boxes_.insert(std::make_pair(d.first, ))


                }

            }


        protected:



    };


}


#endif