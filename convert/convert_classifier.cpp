
#include "opencv2/opencv.hpp"
#include <fstream>
#include <string>
#include "utils/colors.h"
#include "utils/utils.hpp"
#include "data/dataset.hpp"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "core/common.hpp"

using namespace std;
using namespace cv;
using namespace kurff;




DEFINE_string(path, "./icdar2013/",
        "the save path of image");
DEFINE_int32(resize_width, 64, "Width images are resized to");
DEFINE_int32(resize_height, 64, "Height images are resized to");

int main(int argc, char** argv){
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    string path = FLAGS_path;
    int resize_height = FLAGS_resize_height;
    int resize_width = FLAGS_resize_width;

    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    dataset->load("icdar2013.txt");
    cv::Mat img;
    vector<vector<Box> > annotation;
    int cnt = 0;
    ofstream ofs("label.txt");
    for(int i = 0; i < dataset->size(); ++ i){
        LOG(INFO)<< i << " th images";
        dataset->get(i, img, annotation);
        int height = img.rows;
        int width = img.cols;
        for(auto ano : annotation){
            for(auto box : ano){            
                Box b = expand_box(box, 1.2, height, width);
                if( b.width<=0 || b.height <=0 ) continue;
                cv::Mat sub = img(Rect(b.x, b.y, b.width, b.height));
                cv::resize(sub,sub,Size(resize_width, resize_height));
                
                cv::imshow("des", sub);
                string name = path + "/" + std::to_string(cnt)+".png";
                //for(int j = 0; j < b.label_name_.size(); ++ j){
                //    LOG(INFO)<<b.label_name_[j];
                //}
                //LOG(INFO)<< box.label_name_[0];

                auto it = map_string2int.find(box.label_name_[0]);
                string label;
                if(it != map_string2int.end()){
                    label = std::to_string(it->second);
                }else{
                    label = std::to_string(map_string2int.size()-1);
                }
                ofs << std::to_string(cnt)+".png "<<label << std::endl;

                ++ cnt;
                cv::imwrite(name, sub);
                cv::waitKey(1);
            }
        }

    }

    ofs.close();






}