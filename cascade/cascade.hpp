#ifndef __CASCADE_HPP__
#define __CASCADE_HPP__
#include <string>
#include <vector>
#include "core/box.hpp"
#include "core/registry.h"
using namespace std;
namespace kurff{
    class Cascade{
        public:
            Cascade(){

            }
            ~Cascade(){

            }

            virtual void run(const Box& box, const vector<float>& theta, Box& box_next) = 0;

        protected:





    };


    CAFFE_DECLARE_REGISTRY(CascadeRegistry, Cascade);
    CAFFE_DEFINE_REGISTRY(CascadeRegistry, Cascade);

    class CascadeRegression: public Cascade{
        public:
            CascadeRegression(){

            }
            ~CascadeRegression(){

            }

            // theta[0] = dx0;
            // theta[1] = dy0;
            // theta[2] = dx1;
            // theta[3] = dy1;

            void run(const Box& box, const vector<float>& theta, Box& box_next){
                int x0 = box.x;
                int y0 = box.y;
                int x1 = box.x + box.width;
                int y1 = box.y + box.height;
                assert(theta.size() ==4);
                box_next.x = x0 + theta[0];
                box_next.y = y0 + theta[1];
                box_next.width = x1 + theta[2] - x0 - theta[0];
                box_next.height = y1 + theta[3] - y1 - theta[1];
            }

        protected:


    };
    CAFFE_REGISTER_CLASS(CascadeRegistry, CascadeRegression, CascadeRegression);



}

#endif