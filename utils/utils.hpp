#ifndef __KURFF_UTILS_HPP_
#define __KURFF_UTILS_HPP_
#include "core/box.hpp"
#include "glog/logging.h"
#include <vector>
#include <cmath>
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

void overlap(const vector<Box>& proposal, const vector<vector<Box> >& bounding_box, float threshold,
vector<Box>& prune ){
    //LOG(INFO)<<"";
    prune.clear();
    for(auto prop : proposal){
        float o = 0.0f;
        float ov = 0.0f;
        for(auto box : bounding_box){
            for(auto b: box){
                ov = overlap(prop, b);
                if( o <= ov){
                    o = ov;
                }
            }
        }
        if(o <= threshold){
            prune.push_back(prop);
        }
    }
}



void overlap_positive(const vector<Box>& proposal, const vector<vector<Box> >& bounding_box, float threshold,
vector<Box>& prune ){
    //LOG(INFO)<<"";
    prune.clear();
    for(auto prop : proposal){
        float o = 0.0f;
        float ov = 0.0f;
        for(auto box : bounding_box){
            for(auto b: box){
                ov = overlap(prop, b);
                if( o <= ov){
                    o = ov;
                }
            }
        }
        if(o >= threshold){
            prune.push_back(prop);
        }
    }
}

// return the index of overlapping index
// the size of index is same to proposal

void overlap(const vector<Box>& proposal, const vector<Box>& bounding_box, float threshold,
vector<int>& index ){
    //LOG(INFO)<<"";
    index.clear();
    for(auto prop : proposal){
        float o = 0.0f;
        float ov = 0.0f;
        int cnt = -1;
        int best = 0;
        for(auto box : bounding_box){
            ++ cnt;       
            ov = overlap(prop, box);
            if( o <= ov){
                o = ov;
                best = cnt;
            }
        }
        if(o > threshold){
            index.push_back(best);
        }else{
            index.push_back(-1);
        }
    }
}

// bool compare(const TextBox& t0, const TextBox& t1){
//     return t0.confidence_ > t1.confidence_;
// }

void merge_box(const Box& b1, const Box& b2, Box& b3){
    b3.x = std::min(b1.x, b2.x);
    b3.y = std::min(b1.y, b2.y);
    int x1 = b1.x + b1.width;
    int y1 = b1.y + b1.height;

    int x2 = b2.x + b2.width;
    int y2 = b2.y + b2.height;

    int x = std::max(x1,x2);
    int y = std::max(y1,y2);

    b3.width = x - b3.x;
    b3.height = y - b3.y;

}

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
    bool operator () ( int lindex, int rindex ) const
    {
        return container[ lindex ] > container[ rindex ];
    }
};

vector<int> sort_index(const vector<float>& confidence){
    vector <int> indices( confidence.size(), 0 );
    iota( indices.begin(), indices.end(), 0 );  // found in <numeric>
    sort( indices.begin(), indices.end(), compare_indirect_index <decltype(confidence)> ( confidence ) );
    return indices;
}



Box expand_box(const Box& box, float ratio, int height, int width){
    float cx = float(box.x) + float(box.width)/2.0f;
    float cy = float(box.y) + float(box.height)/2.0f;

    Box box_new;

    float width_box = float(box.width)/2.0f * ratio;
    float height_box = float(box.height)/2.0f * ratio;
    box_new.x = (int)std::max(0.0f, cx - (width_box));
    box_new.y = (int)std::max(0.0f, cy - (height_box));
    
    float ex = std::min(float(width-1), cx + (width_box));
    float ey = std::min(float(height-1), cy + (height_box));

    box_new.width = int(ex - box_new.x);
    box_new.height = int(ey - box_new.y);

    //assert(box_new.width >0);
    //assert(box_new.height>0);

    //LOG(INFO)<< box_new.x <<" "<< box_new.y <<" "<< box_new.width <<" "<< box_new.height;
    //LOG(INFO)<<" "<<width_box<<" "<<height_box;
    //LOG(INFO)<< width <<" "<<height;
    return box_new;
}

bool check_box(const Box& box, int height, int width){
    if(box.x <0 || box.x >= width || box.y < 0 || box.y >= height || box.width <=0 || box.width >= width
    || box.height <=0 || box.height >= height || box.x + box.width >= width || box.y + box.height >= height){
        return false;
    }else{
        return true;
    }

}

void clean_boxes(vector<Box>& box){
    for(int i = box.size()-1 ; i >=0; -- i){
        //LOG(INFO)<< box[i].top_pred_[0].name_;
        if(box[i].top_pred_[0].name_.empty()){
            box.erase(box.begin()+i);
        }
    }

}




}







#endif

