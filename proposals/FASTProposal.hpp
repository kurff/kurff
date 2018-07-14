#ifndef __FAST_PROPOSAL_HPP__
#define __FAST_PROPOSAL_HPP__
#include <vector>
#include "glog/logging.h"
#include "proposals/Proposal.hpp"
#include "proposals/fast/fast.h"
namespace kurff{
    class FASTProposal : public Proposal{
        public:

            FASTProposal(int number_proposals):Proposal(number_proposals){
               
            }
            ~FASTProposal(){

            }

            void run(const Mat& image, vector<Box>& proposals){
                LOG(INFO)<<"result";
                cv::Mat gray;                
                cvtColor(image, gray, CV_BGR2GRAY);
                int number;                
                xy* keypoints = fast9_detect_nonmax(gray.ptr(),gray.cols,gray.rows,gray.cols,10,&number);               
                proposals.clear();
                for(int i = 0; i < number; ++ i){
                    Box box;
                    box.x = keypoints[i].x;
                    box.y = keypoints[i].y;
                    box.height = 10;
                    box.width = 10;
                    proposals.push_back(box);
                }

            }

        protected:


    

    };
    CAFFE_REGISTER_CLASS(ProposalRegistry, FASTProposal, FASTProposal);



}
#endif