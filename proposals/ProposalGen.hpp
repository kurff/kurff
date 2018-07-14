#ifndef __PROPOSAL_GEN_HPP__
#define __PROPOSAL_GEN_HPP__
#include "proposals/Proposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "proposals/FASTProposal.hpp"
#include <vector>
#include <string>
namespace kurff{
    class ProposalGen{
        public:
            ProposalGen(std::vector<std::string> proposal_names): proposal_names_(proposal_names){
                

            }

            ~ProposalGen(){


            }

            
        protected:
            std::vector<std::shared_ptr<Proposal> > proposal_methods_;
            std::vector<std::string> proposal_names_;

    };



}





#endif

