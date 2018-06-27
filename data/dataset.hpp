#ifndef __DATASET_HPP__
#define __DATASET_HPP__
#include "data/data.hpp"
#include "annotation.hpp"
#include "utils/visualization.hpp"
#include "utils/utils.hpp"
#include <assert.h>
#include <fstream>
#include <map>
#include <vector>


using namespace std;
namespace kurff{
    class Dataset{
        public:
            Dataset(string image_path, string anno_path) : image_path_(image_path), anno_path_(anno_path){

            }

            ~Dataset(){

            }

            virtual void load(string file) = 0;

            void show(int index){
                assert(index>=0 && index < files_.size());
                auto it = dataset_.find(files_[index]);
                LOG(INFO)<<"visualize"<< it->second.first;
                cv::Mat img = imread(it->second.first);
                auto itb = bounding_boxes_.find(files_[index]);
                visualize(img, *(itb->second), Scalar(0,0,255) );
                cv::imshow("src", img);
                cv::waitKey(0);
            }

            int size(){
                return files_.size();
            }

            cv::Mat get(int index){
                assert(index>=0 && index < files_.size());
                auto it = dataset_.find(files_[index]);
                LOG(INFO)<<"visualize"<< it->second.first;
                cv::Mat img = imread(it->second.first);      
                return img;
            }

            void get(int index, cv::Mat& image, vector<vector<Box> >& boxes ){
               assert(index>=0 && index < files_.size());
                auto it = dataset_.find(files_[index]);
                LOG(INFO)<<"visualize"<< it->second.first;
                image = imread(it->second.first);      
                auto itb = bounding_boxes_.find(files_[index]);
                boxes = *(itb->second);
            }

            void get(int index, vector<vector<Box> >& boxes){
                assert(index>=0 && index < files_.size());
                auto it = dataset_.find(files_[index]);
                //LOG(INFO)<<"visualize"<< it->second.first;   
                auto itb = bounding_boxes_.find(files_[index]);
                boxes = *(itb->second);            
            }

            void push_proposals(int index, const vector<Box>& proposals){
                std::shared_ptr<vector<Box> > ptr (new vector<Box>() );
                ptr->insert(ptr->begin(), proposals.begin(), proposals.end());
                proposals_.insert(std::make_pair(files_[index], ptr));

            }

            float evaluate(float threshold = 0.5f){
                float o = 0.0f, ov = 0.0f;
                size_t cnt = 0;
                size_t total = 0;
                for(auto ano : bounding_boxes_){
                    auto it = proposals_.find( ano.first );
                    for(auto vbox : *(ano.second)){
                        total += vbox.size();
                        for(auto b : vbox){
                            o = 0.0f;
                            for(auto t : *(it->second)){
                                ov = overlap( b, t);
                                if( o <= ov ){
                                    o = ov;
                                }
                            }
                            if(o > threshold){
                                ++ cnt;
                            }
                        }
                    }
                }
                return float(cnt) / float(total);
            }

            float precision(float threshold = 0.5f){
                

            }



        protected:
            std::map<string, std::pair< string , string> > dataset_;
            std::unique_ptr<DataReader> data_reader_;
            std::unique_ptr<Annotation> anno_reader_;
            string image_path_;
            string anno_path_;
            vector<string> files_;
            std::map<string , std::shared_ptr< vector<vector<Box> > > > bounding_boxes_;
            std::map<string,  std::shared_ptr< vector<Box> > > proposals_;

    };

    CAFFE_DECLARE_REGISTRY(DatasetRegistry, Dataset, string, string);
    CAFFE_DEFINE_REGISTRY(DatasetRegistry, Dataset, string , string);

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
                    std::shared_ptr<vector<vector<Box> > > ptr(new vector<vector<Box> >() );
                    this->anno_reader_->load(d.second.second, *ptr);
                    this->bounding_boxes_.insert(std::make_pair(d.first, ptr));
                    
                }

            }


        protected:



    };
    CAFFE_REGISTER_CLASS(DatasetRegistry, ICDAR2013Dataset, ICDAR2013Dataset);

}


#endif