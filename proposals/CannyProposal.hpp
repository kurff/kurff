#ifndef __CANNY_PROPOSAL__
#define __CANNY_PROPOSAL__
#include "proposals/Proposal.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
namespace kurff{
    class CannyProposal : public Proposal{
        public:
            CannyProposal(int number_proposals, int ratio = 3, int lowThreshold = 20, int kernel_size = 3): Proposal(number_proposals)
            , ratio_(ratio), lowThreshold_(lowThreshold), kernel_size_(kernel_size), ratio_size_(1.3f){

            }
            ~CannyProposal(){

            }

            void run(const Mat& image, vector<Box>& proposals){
                cv::Mat gray;

                //LOG(INFO)<< "row: "<< image.rows;
                cvtColor( image, gray, CV_BGR2GRAY );
                cv::Mat edges;
                blur( gray, edges, Size(3,3) );
                Canny( edges, edges, 20, 100, kernel_size_ );
                cv::Mat labels, stats, centroids;
                int number = cv::connectedComponentsWithStats (edges, labels, stats, centroids);
                //for()
                LOG(INFO)<< "rows: " << stats.rows <<" cols: "<<stats.cols;
                //imshow("canny", edges);
                //waitKey(0);
                proposals.clear();
                for(int i = 1; i < stats.rows; ++ i){
                    Box box;
                    int height = stats.at<int>(i, CC_STAT_HEIGHT);
                    int width = stats.at<int>(i, CC_STAT_WIDTH );
                    int max_size = std::max(height, width);
                    int size = ratio_size_* max_size;
                    
                    int cx = stats.at<int>(i,CC_STAT_LEFT ) + width/2;
                    int cy = stats.at<int>(i,CC_STAT_TOP) + height/2;
                    box.x = std::max(0, cx - size/2);
                    box.y = std::max(0, cy  - size/2);

                    int xe = std::min(cx + size/2, image.cols-1);
                    int ye = std::min(cy + size/2, image.rows-1);

                    //assert(xe > box.x);
                    //assert(ye > box.y);
                    box.width = std::max(xe - box.x,1);
                    box.height = std::max(ye - box.y,1);
                    proposals.push_back(box);
                }




            }
        protected:
            int ratio_;
            int lowThreshold_;
            int kernel_size_;
            float ratio_size_;
            


    };
    CAFFE_REGISTER_CLASS(ProposalRegistry, CannyProposal, CannyProposal);

}




#endif