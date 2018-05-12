#ifndef __PROPOSAL_HPP__
#define __PROPOSAL_HPP__
#include "opencv2/opencv.hpp"
#include "core/box.hpp"
#include "core/registry.h"
using namespace cv;
namespace kurff{
    class Proposal{
        public:
            Proposal(int number_proposals): number_proposals_(number_proposals){

            }
            ~Proposal(){

            }
            int number_proposals(){return number_proposals_;}

            virtual void run(const Mat& image, vector<Box>& proposals) = 0;
        protected:
            int number_proposals_;
            string name_;
    };
    CAFFE_DECLARE_REGISTRY(ProposalRegistry, Proposal, int);
    CAFFE_DEFINE_REGISTRY(ProposalRegistry, Proposal, int);





}

#endif