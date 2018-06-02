#ifndef __DATA_HPP__
#define __DATA_HPP__
#include <string>
#include <vector>
using namespace std;

namespace kurff{
    class Data{
        public:
            Data(){

            }
            ~Data(){

            }

            virtual void load_train() = 0;
            virtual void load_val() = 0;
            virtual void load_test() = 0;
        protected:
            vector<string> train_image_names_;
            vector<string>  test_image_names_;
            vector<string> val_image_names_;

            



    };

    class ICDAR2013 : public Data{
        public:
            ICDAR2013(){

            }
            ~ICDAR2013(){

            }
        protected:


    };




}




#endif