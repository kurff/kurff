#ifndef __KURFF_UTILS_HPP_
#define __KURFF_UTILS_HPP_
#include "core/box.hpp"
#include "glog/logging.h"
#include <vector>
using namespace std;
namespace kurff{

float overlap(const Box& b0, const Box& b1){
    int b0_x0 = b0.x;
    int b0_y0 = b0.y;
    int b0_x1 = b0.x + b0.width;
    int b0_y1 = b0.y + b0.height;

    int b1_x0 = b1.x;
    int b1_y0 = b1.y;
    int b1_x1 = b1.x + b1.width;
    int b1_y1 = b1.y + b1.height;

    if(b0_y0 > b1_y1){
        return 0.0f;
    }
    if(b0_x0 > b1_x1){
        return 0.0f;
    }
    if(b0_y1 < b1_y0){
        return 0.0f;
    }
    if(b0_x1 < b1_x0){
        return 0.0f;
    }

    float x = min(b0_x1,b1_x1) - max(b0_x0,b1_x0);
    float y = min(b0_y1,b1_y1) - max(b0_y0,b1_y0);
    float intersection = x*y;
    float a0 = (b0_y1-b0_y0)*(b0_x1-b0_x0);
    float a1 = (b1_y1-b1_y0)*(b1_x1-b1_x0);
    return intersection /(a0+a1-intersection);
}

void overlap(vector<Box>& proposal, const vector<vector<Box> >& bounding_box, float threshold = 0.5 ){
    LOG(INFO)<<"before size: "<< proposal.size();
    for( auto it = proposal.begin(); it != proposal.end();  ){
        float o = 0.0f;
        float ov = 0.0f;
        for(auto box : bounding_box ){
            for(auto b : box){
                ov = overlap(*it, b);
                if( o <= ov ){
                    o = ov;
                }
            }
        }
        //LOG(INFO)<<"overlap: "<< o;
        if(o<=threshold){
            it = proposal.erase(it);
        }else{
            ++ it;
        }
    }
    LOG(INFO)<<"after size: "<< proposal.size();
}


// bool compare(const TextBox& t0, const TextBox& t1){
//     return t0.confidence_ > t1.confidence_;
// }



void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
 
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

template <typename Container>
struct compare_indirect_index
{
    const Container& container;
    compare_indirect_index( const Container& container ): container( container ) { }
    bool operator () ( size_t lindex, size_t rindex ) const
    {
        return container[ lindex ] < container[ rindex ];
    }
};

vector<size_t> sort_index(const vector<float>& confidence){
    vector <size_t> indices( confidence.size(), 0 );
    iota( indices.begin(), indices.end(), 0 );  // found in <numeric>
    sort( indices.begin(), indices.end(), compare_indirect_index <decltype(confidence)> ( confidence ) );
    return indices;
}





}







#endif

