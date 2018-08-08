#include "data/dataset.hpp"
#include "proposals/ProposalGen.hpp"
#include "proposals/Merge.hpp"
#include "utils/colors.h"
#include "utils/utils.hpp"
using namespace kurff;
int main(){
    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    dataset->load("icdar2013.txt");
    vector<string> proposal_name={"Canny","MSER"};
    std::shared_ptr<ProposalGen> proposal_method (new ProposalGen(proposal_name));
    proposal_method->create();
    for(int i = 0; i < dataset->size(); ++ i){
        //dataset->show(i);
        LOG(INFO)<< i << " th images";
        cv::Mat img;
        // = dataset->get(i);
        vector<vector<Box> > annotation;
        dataset->get(i, img, annotation);
        vector<Box> proposals;
        proposal_method->run(img, proposals);
        visualize(img,proposals,Colors::Red);
        cv::imshow("proposal",img);
        cv::waitKey(0);
    }
    for(float r = 0.1f; r < 1.0f; r += 0.1){
        LOG(INFO)<<"recall: "<<dataset->evaluate(r);
    }


    return 0;
}