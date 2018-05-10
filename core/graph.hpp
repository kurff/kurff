#ifndef __KURFF_GRAPH_HPP__
#define __KURFF_GRAPH_HPP__
#include "opencv2/opencv.hpp"
#include "character.hpp"
#include "glog/logging.h"
#include <map>
#include "common.hpp"
using namespace std;
using namespace cv;
namespace kurff{


template<typename T>
class Node{
    public:
        Node(){

        }
        ~Node(){

        }
    protected:
        T data_;

};


template<typename D>
class Edge{
    public:
        Edge(){

        }
        ~Edge(){

        }
    protected:
        D data_;

};



class Graph{
    public:
        Graph(){

        }

        ~Graph(){


        }

        


    protected:

};



}









#endif