#include "proposals/Proposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "proposals/FASTProposal.hpp"
#include "utils/visualization.hpp"
#include "utils/colors.h"
#include <memory>
using namespace kurff;
int main(int argc, char* argv[]){
    std::shared_ptr<Proposal> proposal (ProposalRegistry()->Create("FASTProposal",100));

    vector<Box> boxes;
    cv::Mat image = cv::imread(argv[1]);
    cv::imshow("src", image);
    cv::waitKey(0);
    proposal->run(image,boxes);
    if(boxes.size()>=1)
    LOG(INFO)<< boxes[0].x<<" "<<boxes[0].y;
    visualize<Box>(image, boxes, Colors::Red);
    cv::imwrite("result.jpg",image);
    return 0;
}