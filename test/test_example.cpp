#include "data/dataset.hpp"
#include "utils/colors.h"
#include "utils/utils.hpp"

using namespace kurff;
int main(){
    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    
    dataset->load("icdar2013.txt");
    for(int i = 0; i < dataset->size(); ++ i){
        //dataset->show(i);
        LOG(INFO)<< i << " th images";
        cv::Mat img;
        // = dataset->get(i);
        cv::Mat gray;
        vector<vector<Box> > annotation;
        dataset->get(i, img, annotation);
        cvtColor( img, gray, CV_BGR2GRAY );
        Canny( gray, gray, 20, 100, 3 );

        cv::imshow("canny", gray);
        cv::waitKey(0);

    }
    return 0;
}