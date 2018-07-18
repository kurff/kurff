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
                canny_=ProposalRegistry()->Create("CannyProposal", 200);
                mser_ = ProposalRegistry()->Create("MSERProposal",100);
                model_=ModelRegistry()->Create("Classifier",1);
                model_->init("../script/deploy.prototxt","../build/hard_model/_iter_100000.caffemodel",1);
            }
            ~Framework(){

            }


            void run(const Mat& image, vector<Box>& result){
                canny_->run(image, result);
                LOG(INFO)<<"canny proposal: "<< result.size();
                vector<Box> mser_boxes;
                mser_->run(image, mser_boxes);
                LOG(INFO)<<"mser proposal: "<< mser_boxes.size();
                result.insert(result.end(), mser_boxes.begin(), mser_boxes.end());
                model_->run(image, result);
            }


            void run_given_box(const Mat& image, vector<Box>& result){
                model_->run(image, result);
            }




        protected:
            std::shared_ptr<Proposal> canny_;
            std::shared_ptr<Proposal> mser_;
            std::shared_ptr<Model> model_;

    };

    class CascadeFramework{
        public:
            CascadeFramework(){
                proposal_=ProposalRegistry()->Create("CannyProposal", 200);
                regression_=ModelRegistry()->Create("Regression",1);
                regression_->init("../script/deploy.prototxt","../build/_iter_95000.caffemodel",1);
            }
            ~CascadeFramework(){

            }
        protected:
            std::shared_ptr<Proposal> proposal_;
            std::shared_ptr<Model> regression_;


    };

}



#endif