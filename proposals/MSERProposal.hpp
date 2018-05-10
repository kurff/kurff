#ifndef __MSERPROPOSAL_HPP__
#define __MSERPROPOSAL_HPP__

#include <memory>
#include "proposals/mser.h"
#include "proposals/Proposal.hpp"

namespace kurff{    
    class MSERProposal: public Proposal{
        public:
            MSERProposal(int number_proposals): Proposal(number_proposals){
                mser_.reset(new kurff::MSER());
            }
            ~MSERProposal(){

            }

            void run(const Mat& image, vector<Box>& proposals){
                

            }

        protected:
            std::shared_ptr<kurff::MSER> mser_;


    };
    CAFFE_REGISTER_CLASS(ProposalRegistry, MSERProposal, MSERProposal);

}
#endif