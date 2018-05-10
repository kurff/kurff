#ifndef __KURFF_PROCESS_HPP__
#define __KURFF_PROCESS_HPP__
#include "utils/character.hpp"

namespace kurff{
class Process{
    public:
        Process(){

        }
        ~Process(){

            
        }
        virtual void run(Character& characters) = 0;
};

class PruneProcess: public Process{
    public:
        PruneProcess(){

        }
        ~PruneProcess(){

        }
    private:
        void run(Character& characters){
            

        }


};





}




#endif