#ifndef __CANNY_PROPOSAL__
#define __CANNY_PROPOSAL__
#include "proposals/Proposal.hpp"
#include "opencv2/opencv.hpp"
#include <memory>
namespace kurff{
    class CannyProposal : public Proposal{
        public:
            CannyProposal(int number_proposals, int ratio = 3, int lowThreshold = 20, int kernel_size = 3): Proposal(number_proposals)
            , ratio_(ratio), lowThreshold_(lowThreshold), kernel_size_(kernel_size){

            }
            ~CannyProposal(){

            }

            void run(const Mat& image, vector<Box>& proposals){
                cv::Mat gray;

                LOG(INFO)<< "row: "<< image.rows;
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
                for(int i = 0; i < stats.rows; ++ i){
                    Box box;
                    box.x = stats.at<int>(i,CC_STAT_LEFT ) ;
                    box.y = stats.at<int>(i,CC_STAT_TOP);
                    box.width = stats.at<int>(i, CC_STAT_WIDTH );
                    box.height = stats.at<int>(i, CC_STAT_HEIGHT);
                    proposals.push_back(box);
                }


            }
        protected:
            int ratio_;
            int lowThreshold_;
            int kernel_size_;
            


    };
    CAFFE_REGISTER_CLASS(ProposalRegistry, CannyProposal, CannyProposal);

}




#endif