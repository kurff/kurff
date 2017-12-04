#ifndef __KURFF_SUBTITLE_HPP__
#define __KURFF_SUBTITLE_HPP__

#include "utils/process.hpp"
#include "utils/character.hpp"
#include "utils/classifier.hpp"
#include "utils/grammar.hpp"
#include "utils/text.hpp"
#include "glog/logging.h"
#include "utils/visualization.hpp"
#include <string>
#include <memory>
using namespace std;
namespace kurff{
class Subtitle{
    public:
        Subtitle(){


        }
        ~Subtitle(){


        }

        void init(string model_def, string model){
            character_ = shared_ptr<Character>( new MSERCharacter());
            classifier_ = shared_ptr<Classifier>(new CNNClassifier());
            grammar_ = shared_ptr<Grammar>(new BiGrammar() );
            classifier_->initial(model_def, model);


            
            //text_ = shared_ptr<Text>()

        }

        void run(const Mat& input, vector<Box>& boxes){
           












        }

    private:
        shared_ptr<Character> character_;
        shared_ptr<Classifier> classifier_;
        shared_ptr<Grammar> grammar_;
        shared_ptr<DetectorGrammar> detector_grammar_;
       //DetectorGrammar* detector_grammar_;
        //shared_ptr<Text> text_;
        



};

}






#endif