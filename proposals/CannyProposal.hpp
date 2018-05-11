#ifndef __CANNY_PROPOSAL__
#define __CANNY_PROPOSAL__
#include "proposals/Proposal.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
namespace kurff{
    class CannyProposal : public Proposal{
        public:
            CannyProposal(int number_proposals, int ratio = 3, int lowThreshold = 50, int kernel_size = 3): Proposal(number_proposals)
            , ratio_(ratio), lowThreshold_(lowThreshold), kernel_size_(kernel_size){

            }
            ~CannyProposal(){

            }

            void run(const Mat& image, vector<Box>& proposals){
                cv::Mat gray;
                cvtColor( image, gray, CV_BGR2GRAY );
                cv::Mat edges;
                blur( image, edges, Size(3,3) );
                Canny( edges, edges, lowThreshold_, lowThreshold_*ratio_, kernel_size_ );
                

            }
        protected:
            int ratio_;
            int lowThreshold_;
            int kernel_size_;
            


    };
    CAFFE_REGISTER_CLASS(ProposalRegistry, CannyProposal, CannyProposal);

}




#endif