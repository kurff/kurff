#ifndef __KURFF_GRAMMAR_HPP__
#define __KURFF_GRAMMAR_HPP__
#include "utils/character.hpp"
#include "utils/utils.hpp"
#include "utils/graph.hpp"
#include "glog/logging.h"
namespace kurff{

class Grammar{
    public:
        Grammar(){

        }
        ~Grammar(){

        }
        virtual float score(Character& characters) = 0;

    private:
        


};

class BiGrammar: public Grammar{
    public:
        BiGrammar(){

        }
        ~BiGrammar(){

        }

        float score(Character& characters){
            
        }
    private:
};

// Horizontal Text Grammar
// Assume the characters formulating a line

class DetectorGrammar{
    public:
        DetectorGrammar(){

        }
        ~DetectorGrammar(){

        }

        DetectorGrammar(const DetectorGrammar& other){
            LOG(INFO)<<"DetectorGrammar "<<other.best_.size();
            best_.resize(other.best_.size());
            
            copy(other.best_.begin(),other.best_.end(),best_.begin());
            //for(int i = 0; i < other.get_best_result().size(); ++ i){
            //    best_[i] = other.best_[i];
            //    LOG(INFO)<<"other "<<other.get_best_result()[i].x0_<<" mine: "<<best_[i].x0_;
            //}
            text_.resize(other.text_.size());
            copy(other.text_.begin(),other.text_.end(),text_.begin());

        }
        
        virtual float score(Character& characters) {
            return 0.0f;
        } 
        vector<Box> get_best_result() const{
            return best_;
        }
        size_t get_number() const {
            return best_.size();
        }
        int x0(size_t idx) const {
            return best_[idx].x0_;
        }
        int y0(size_t idx)const {
            return best_[idx].y0_;
        }
        int h(size_t idx)const {
            return best_[idx].h_;
        }
        int w(size_t idx)const {
            return best_[idx].w_;
        }

        size_t get_text_number() const {
            return text_.size();
        }
        int c0(size_t idx) const {
            return text_[idx].x0_;
        }
        int r0(size_t idx) const {
            return text_[idx].y0_;
        }
        int h0(size_t idx) const {
            return text_[idx].h_;
        }
        int w0(size_t idx) const {
            return text_[idx].w_;
        }
        float f(size_t idx) const {
            return text_[idx].confidence_;
        }


    protected:

        vector<Box> best_;
        vector<TextBox> text_;




};




} //end of namespace


#endif