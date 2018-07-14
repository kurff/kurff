#include "framework/framework.hpp"
#include "utils/visualization.hpp"

#include "data/dataset.hpp"
#include "proposals/Proposal.hpp"
#include "proposals/MSERProposal.hpp"
//#include "proposals/FASTProposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "proposals/Merge.hpp"
#include "utils/colors.h"
#include "utils/utils.hpp"
#include <string>
using namespace std;
using namespace kurff;

int main(int argc, char* argv[]){
    std::shared_ptr<Framework> framework (new Framework());
    // string path = argv[1];
    // for(int i = 100; i < 325; ++ i){
    // //for(int i = 1; i <= 233; ++ i ){
    //     //cv::Mat image = cv::imread(path+"/img_"+std::to_string(i)+".jpg");
    //     cv::Mat image = cv::imread(path+"/"+std::to_string(i)+".jpg");
    //     vector<Box> boxes;
    //     framework->run(image, boxes);
    //     visualize(image, boxes, Scalar(0,255,0), true);
    //     LOG(INFO)<< path +"/"+std::to_string(i)+".jpg";
    //     cv::imshow("src", image);
    //     cv::imwrite("result_test/"+std::to_string(i)+".jpg", image);
    //     cv::waitKey(1);
    // }

    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    std::shared_ptr<Proposal> mser (ProposalRegistry()->Create("MSERProposal",100));
    std::shared_ptr<Proposal> canny (ProposalRegistry()->Create("CannyProposal",100));
    //std::shared_ptr<Proposal> fast (ProposalRegistry()->Create("FASTProposal", 100));

    dataset->load("icdar2013.txt");
    for(int i = 0; i < dataset->size(); ++ i){
        //dataset->show(i);
        LOG(INFO)<< i << " th images";
        cv::Mat img;
        // = dataset->get(i);
        vector<vector<Box> > annotation;
        dataset->get(i, img, annotation);
        vector<Box> mser_boxes;
        vector<Box> canny_boxes;
        //mser->run(img, canny_boxes);
        
        //canny->run(img, canny_boxes);
        //vector<Box> fast_boxes;
        //fast->run(img, fast_boxes);
        //overlap(mser_boxes, annotation);
        //canny_boxes.insert(canny_boxes.begin(), mser_boxes.begin(), mser_boxes.end());

        LOG(INFO)<< "size of proposal: "<< canny_boxes.size();
        framework->run(img, canny_boxes);
        clean_boxes(canny_boxes);
        LOG(INFO)<<" size of predict: "<< canny_boxes.size();
        dataset->push_proposals(i, canny_boxes);
        //overlap(canny_boxes, annotation);
        //LOG(INFO)<<"test overlap" << overlap(mser_boxes[0], mser_boxes[0]);
        string name = dataset->get_file(i);
        visualize(img, canny_boxes, Colors::GreenYellow, true);
        //visualize<Box>(vis_mser, mser_boxes, Colors::Green);
        //cv::imshow("mser", img);
        //cv::waitKey(0);

        cv::imwrite("mser_canny_framework/"+name+".png", img);
    }
    for(float r = 0.1f; r < 1.0f; r += 0.1){
        LOG(INFO)<<"recall: "<<dataset->evaluate(r);
    }

    return 0;
}