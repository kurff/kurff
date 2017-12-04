#include "subtitle.hpp"
#include <string>
using namespace std;
#include "opencv2/opencv.hpp"
using namespace cv;

int main(int argc, char* argv[]){
    string model_def = " ";
    string model = " ";
    kurff::Subtitle* subtitle = new kurff::Subtitle();
    subtitle->init(model_def, model);
    vector<kurff::Box> boxes;
    string file_name = argv[1];
    Mat image = imread(file_name.c_str());
    subtitle->run(image, boxes);
    




    return 1;


}   
