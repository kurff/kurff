#ifndef __KURFF_GRAPH_HPP__
#define __KURFF_GRAPH_HPP__
#include "opencv2/opencv.hpp"
#include "character.hpp"
#include "glog/logging.h"
using namespace cv;
namespace kurff{

class Graph{
    public:
        Graph(){

        }

        ~Graph(){


        }

        virtual void build(const Character& characters) = 0;


    protected:

};

// Horizontal Graph
class HorGraph: public Graph{
    public:
        HorGraph(){

        }
        ~HorGraph(){

        }

        void build(const Character& characters){
           

        }
    private:


};

}









#endif