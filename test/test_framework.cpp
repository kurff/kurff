#include "framework/framework.hpp"
#include "utils/visualization.hpp"
using namespace kurff;

int main(int argc, char* argv[]){
    std::shared_ptr<Framework> framework (new Framework());
    cv::Mat image = cv::imread(argv[1]);
    vector<Box> boxes;
    framework->run(image, boxes);

    visualize(image, boxes, Scalar(0,255,0), true);

    cv::imshow("src", image);

    cv::waitKey(0);

    return 0;
}