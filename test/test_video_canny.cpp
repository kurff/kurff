#include "proposals/Proposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "proposals/FASTProposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "utils/visualization.hpp"
#include "utils/colors.h"
#include <memory>
using namespace kurff;
int main(int argc, char* argv[]){
    std::shared_ptr<Proposal> proposal (ProposalRegistry()->Create("FASTProposal",100));
    vector<Box> boxes;

    cv::VideoCapture cap(argv[1]);

    cv::Mat image;


    

    vector<Box> mser_boxes;
    std::shared_ptr<Proposal> mser (ProposalRegistry()->Create("MSERProposal",100));
    std::shared_ptr<Proposal> canny (ProposalRegistry()->Create("CannyProposal",100));
    //mser->run(image, mser_boxes);

    while(1){
        // proposal->run(image,boxes);
        // if(boxes.size()>=1)
        // LOG(INFO)<< boxes[0].x<<" "<<boxes[0].y;
        // cv::Mat vis_mser;
        // image.copyTo(vis_mser);
        // visualize<Box>(vis_mser, mser_boxes, Colors::Red);
        // cv::imwrite("mser_result.jpg", vis_mser);

        // cv::Mat vis_fast;
        // image.copyTo(vis_fast);
        // visualize<Box>(vis_fast, boxes, Colors::Red);
        // cv::imwrite("fast_result.jpg",vis_fast);
        cap >>  image;
        if(image.empty()) break;
        vector<Box> canny_boxes;

        canny->run(image, canny_boxes);
    

        cv::Mat vis_canny;
        image.copyTo(vis_canny);
        visualize(vis_canny, canny_boxes, Colors::Red);
        cv::Mat show;
        cv::resize(vis_canny, show,cv::Size(vis_canny.cols/2, vis_canny.rows/2));
        cv::imshow("edge proposal", show);

        cv::waitKey(1);

    }
    



    //cv::imwrite("canny_result.jpg",vis_canny);
    return 0;
}