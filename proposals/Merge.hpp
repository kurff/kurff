#ifndef __MERGE_HPP__
#define __MERGE_HPP__
#include "proposals/Proposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "utils/utils.hpp"
#include <vector>
using namespace std;
// merge proposal using simple overlapping theshold
namespace kurff{
    class Merge{
        public:
            Merge(){}
            ~Merge(){}
            
            void merge(const vector<Box>& proposal1, const vector<Box>& proposal2, 
            vector<Box>& proposal){
                proposal.clear();
                vector<int> index;
                overlap(proposal1, proposal2, 0.7, index);
                
                

            }
        protected:


    };


}

#endif