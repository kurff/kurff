#include "framework/framework.hpp"
#include "utils/visualization.hpp"
#include <string>
using namespace std;
using namespace kurff;

int main(int argc, char* argv[]){
    std::shared_ptr<Framework> framework (new Framework());
    string path = argv[1];
    for(int i = 1; i <= 233; ++ i ){
        cv::Mat image = cv::imread(path+"/img_"+std::to_string(i)+".jpg");
        vector<Box> boxes;
        framework->run(image, boxes);

        visualize(image, boxes, Scalar(0,255,0), true);

        //cv::imshow("src", image);
        cv::imwrite("result_test/"+std::to_string(i)+".jpg", image);
        //cv::waitKey(0);
    }


    return 0;
}