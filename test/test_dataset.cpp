#include "data/dataset.hpp"
#include "proposals/Proposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "proposals/FASTProposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "proposals/Merge.hpp"
#include "utils/colors.h"
#include "utils/utils.hpp"
using namespace kurff;
int main(){
    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    std::shared_ptr<Proposal> mser (ProposalRegistry()->Create("MSERProposal",100));
    std::shared_ptr<Proposal> canny (ProposalRegistry()->Create("CannyProposal",100));
    std::shared_ptr<Proposal> fast (ProposalRegistry()->Create("FASTProposal", 100));
    Merge* merge = new Merge();
    dataset->load("icdar2013.txt");
    for(int i = 0; i < dataset->size(); ++ i){
        //dataset->show(i);
        LOG(INFO)<< i << " th images";
        cv::Mat img;
        // = dataset->get(i);
        vector<vector<Box> > annotation;
        dataset->get(i, img, annotation);
        vector<Box> mser_boxes;
        mser->run(img, mser_boxes);
        vector<Box> canny_boxes;
        canny->run(img, canny_boxes);
        //vector<Box> fast_boxes;
        //fast->run(img, fast_boxes);
        //overlap(mser_boxes, annotation);

        //canny_boxes.insert(canny_boxes.begin(), mser_boxes.begin(), mser_boxes.end());
        
        vector<Box> prune;
        merge->merge(canny_boxes, mser_boxes, prune); 
        
        dataset->push_proposals(i, prune);


        //overlap(canny_boxes, annotation);
        //LOG(INFO)<<"test overlap" << overlap(mser_boxes[0], mser_boxes[0]);
        cv::Mat vis_mser;
        img.copyTo(vis_mser);
        //visualize<Box>(vis_mser, canny_boxes, Colors::Red);

        //visualize<Box>(vis_mser, mser_boxes, Colors::Green);
        //cv::imshow("mser", vis_mser);
        //cv::waitKey(0);
        //cv::imwrite("mser/"+std::to_string(i)+".png", vis_mser);
    }
    for(float r = 0.1f; r < 1.0f; r += 0.1){
        LOG(INFO)<<"recall: "<<dataset->evaluate(r);
    }


    return 0;
}