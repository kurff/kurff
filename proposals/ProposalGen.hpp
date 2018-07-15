#ifndef __PROPOSAL_GEN_HPP__
#define __PROPOSAL_GEN_HPP__
#include "proposals/Proposal.hpp"
#include "proposals/MSERProposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "proposals/FASTProposal.hpp"
#include "proposals/Merge.hpp"
#include <vector>
#include <string>
namespace kurff{
    class ProposalGen{
        public:
            ProposalGen(std::vector<std::string> proposal_names): proposal_names_(proposal_names), number_(100){
                
                
            }

            ~ProposalGen(){


            }

            void create(){
                proposal_methods_.clear();
                
                for(auto name : proposal_names_){
                    LOG(INFO)<<"create proposal methods: "<< name;
                    proposal_methods_.push_back(ProposalRegistry()->Create(name+"Proposal", number_));
                }
                merge_.reset(new Merge());
            }

            void run(const cv::Mat& image, std::vector<Box>& proposals ){
                proposals_.resize(proposal_methods_.size());
                int cnt = -1;
                for(auto proposal_method : proposal_methods_){
                    ++ cnt;
                    proposal_method->run(image, proposals_[cnt]);
                    LOG(INFO)<<proposal_method->name()<<" get proposals: "<<proposals_[cnt].size();
                }
                for(int i = 0; i < proposal_methods_.size(); ++ i){
                    merge_->simple_merge(proposals, proposals_[i], proposals);
                }
            }

            
        protected:
            std::vector<std::shared_ptr<Proposal> > proposal_methods_;
            std::shared_ptr<Merge> merge_;
            std::vector<std::vector<Box> > proposals_;
            std::vector<std::string> proposal_names_;
            int number_;

    };



}





#endif

