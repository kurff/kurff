#ifndef __MSERPROPOSAL_HPP__
#define __MSERPROPOSAL_HPP__

#include <memory>
#include "proposals/mser/mser.h"
#include "proposals/Proposal.hpp"
#include "opencv2/opencv.hpp"
#include "glog/logging.h"
#include "utils/utils.hpp"
namespace kurff{    
    class MSERProposal: public Proposal{
        public:
            MSERProposal(int number_proposals): Proposal(number_proposals){
                mser8_.reset(new kurff::MSER(2, 0.0001, 0.1, 0.5, 0.5, true));
                mser4_.reset(new kurff::MSER(2,0.0001,0.1,0.5,0.5,false));
                this->name_ = "MSER";
            }
            ~MSERProposal(){

                
            }

            void run(const Mat& image, vector<Box>& proposals){
                cv::Mat gray;
                cvtColor(image, gray, CV_BGR2GRAY);
                mser8_->operator()(gray.ptr(),gray.cols, gray.rows, region8_);
                cv::Mat inverse = 255-gray;
                mser4_->operator()(inverse.ptr(), gray.cols, gray.rows, region4_);
                proposals.clear();
                convert(region8_, proposals, image.rows, image.cols);
                //LOG(INFO)<< proposals[0].x<<" "<< proposals[0].y;
                convert(region4_, proposals, image.rows, image.cols);
                //LOG(INFO)<<"8: "<< proposals.size();
                
            }

        protected:
            void convert(const vector<kurff::MSER::Region>& region, vector<Box>& proposals, int height, int width){    
                for(auto reg : region){
                    double x = reg.moments_[0]/ reg.area_;
                    double y = reg.moments_[1]/ reg.area_;
                    double a = reg.moments_[2] / reg.area_ - x * x;
                    double b = reg.moments_[3] / reg.area_ - x * y;
                    double c = reg.moments_[4] / reg.area_ - y * y;
                    const double d  = a + c;
	                const double e  = a - c;
	                const double f  = sqrt(4.0 * b * b + e * e);
	                const double e0 = (d + f) / 2.0; // First eigenvalue
	                const double e1 = (d - f) / 2.0; // Second eigenvalue
	
	                // Desired norm of the eigenvectors
	                const double e0sq = sqrt(e0);
                    const double e1sq = sqrt(e1);
                    const double maxR = std::max(e0sq,e1sq);
                    CHECK_GT(maxR, 0);
                    Box box;
                    box.x = std::max<int>(x - 2*maxR,0);
                    box.y = std::max<int>(y - 2*maxR,0.0);

                    int x1 = std::min<int>(box.x + 4*maxR, (width-1));
                    int y1 = std::min<int>(box.y + 4*maxR, (height-1));
                    box.height = y1 - box.y;
                    box.width =  x1 - box.x;
                    //Box box_new = expand_box(box, 1.2, height, width);
                    if(check_box(box, height, width)){
                        proposals.push_back(box);
                    }   
                    //LOG(INFO)<<box.x<<" "<<box.y<<" "<<box.height<<" "<<box.width;
                }

            }

        protected:
            std::shared_ptr<kurff::MSER> mser8_;
            std::shared_ptr<kurff::MSER> mser4_;
            std::vector<kurff::MSER::Region> region8_;
            std::vector<kurff::MSER::Region> region4_;


    };
    CAFFE_REGISTER_CLASS(ProposalRegistry, MSERProposal, MSERProposal);

}
#endif