#include "opencv2/opencv.hpp"
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* argv[]){
    string folder1 = argv[1];
    string folder2 = argv[2];
    string list = argv[3];
    string name;
    ifstream fin(list.c_str(), ios::in);
    while(fin >> name){
        cv::Mat img1 = cv::imread(folder1+"/"+name+".png");
        cv::Mat img2 = cv::imread(folder2+"/"+name+".png");
        cv::Mat img = cv::Mat::zeros(img1.rows,img1.cols*2, CV_8UC3);
        img1.copyTo(img(cv::Rect(0,0,img1.cols,img1.rows)));
        img2.copyTo(img(cv::Rect(img2.cols,0,img2.cols,img2.rows)));
        //imshow("src", img);
        //cv::waitKey(0);
        cv::imwrite("save/"+name+".png", img);

    }

    fin.close();
    

}