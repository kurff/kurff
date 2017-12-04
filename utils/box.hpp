#ifndef __KURFF_BOX_HPP__
#define __KURFF_BOX_HPP__

#include <vector>
#include <string>
using namespace std;
namespace kurff{



class Top{
    public:

    float confidence_;
    int predict_;
    string name_;
    Top(const Top& top){
        confidence_ = top.confidence_;
        predict_ = top.predict_;
        name_ = top.name_;
    }
    Top(){

    }
    ~Top(){

    }


};

class Box{
    public:
        int x0_;
        int y0_;
        int x1_;
        int y1_;
        int h_;
        int w_;
        vector<Top> tops_;
        //float confidence_;
        //string name_;
        //int predict_;
        int label_;
    public:
        Box():x0_(0),y0_(0),x1_(0),y1_(0),h_(0),w_(0),label_(0){

        }
        ~Box(){

        }

        Box(const Box& box){
            x0_ = box.x0_;
            y0_ = box.y0_;
            x1_ = box.x1_;
            y1_ = box.y1_;
            h_ = box.h_;
            w_ = box.w_;
            label_ = box.label_;
            tops_.resize(box.tops_.size());
            copy(box.tops_.begin(),box.tops_.end(),tops_.begin());
        }
};


class TextBox{
    public:
        TextBox():confidence_(0.0f),index_(0), x0_(0),y0_(0),x1_(0),y1_(0),h_(0),w_(0){

        }
        ~TextBox(){

        }

        TextBox(const TextBox& t){
            confidence_ = t.confidence_;
            index_ = t.index_;
            characters_.resize(t.characters_.size());
            copy(t.characters_.begin(), t.characters_.end(), characters_.begin());
            x0_ = t.x0_;
            y0_ = t.y0_;
            x1_ = t.x1_;
            y1_ = t.y1_;
            h_ = t.h_;
            w_ = t.w_;
        }

        void get_bound_box(){
            x0_ = 1e5;
            y0_ = 1e5;
            x1_ = 0;
            y1_ = 0;
            for(size_t i = 0; i < characters_.size(); ++ i){
                if(x0_ >= characters_[i].x0_){
                    x0_ = characters_[i].x0_;
                }
                if(y0_ >= characters_[i].y0_){
                    y0_ = characters_[i].y0_;
                }
                if(x1_ <= characters_[i].x1_){
                    x1_ = characters_[i].x1_;
                }
                if(y1_ <= characters_[i].y1_){
                    y1_ = characters_[i].y1_;
                }             
            }
            h_ = y1_ - y0_;
            w_ = x1_ - x0_;

        }
    public:
        vector<Box> characters_;
        float confidence_;
        int index_;
        int x0_;
        int y0_;
        int x1_;
        int y1_;
        int h_;
        int w_;
};


}







#endif