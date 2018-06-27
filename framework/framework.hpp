#ifndef __FRAME_WORK_HPP__
#define __FRAME_WORK_HPP__
#include "proposals/Proposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "model/model.hpp"
#include "model/regression.hpp"
#include "model/classifier.hpp"
#include "opencv2/opencv.hpp"
#include <vector>
#include "core/box.hpp"
using namespace std;
namespace kurff{
    class Framework{
        public:
            Framework(){
                proposal_=ProposalRegistry()->Create("CannyProposal", 200);
                model_=ModelRegistry()->Create("Classifier",1);
                model_->init("../script/deploy.prototxt","../build/_iter_10000.caffemodel",1);
            }
            ~Framework(){

            }


            void run(const Mat& image, vector<Box>& result){
                proposal_->run(image, result);
                model_->run(image, result);
            }

        protected:
            std::shared_ptr<Proposal> proposal_;
            std::shared_ptr<Model> model_;

    };

    class CascadeFramework{
        public:
            CascadeFramework(){
                proposal_=ProposalRegistry()->Create("CannyProposal", 200);
                model_=ModelRegistry()->Create("Regression",1);
                model_->init("../script/deploy.prototxt","../build/_iter_10000.caffemodel",1);
            }
            ~CascadeFramework(){

            }
        protected:
            std::shared_ptr<Proposal> proposal_;
            std::shared_ptr<Model> regression_;


    };

}



#endif