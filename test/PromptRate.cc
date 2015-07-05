#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include "LeptonAnalyzer.cc"
#include "JetAnalyzer.cc"
#include "GenAnalyzer.cc"
#include "../interface/TreeMaker.h"
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 
#include "../plugins/Macros.cc"


//A script to get the prompt rate for electrons and muons. Usage is ./PromptRate.o <Data,MC> <El,Mu> 

int main(int argc, char* argv[]){

  bool correctusage=false;
  if(argc==3 && (argv[1]!="Data" || argv[1]!="MC") && (argv[2]!="El" || argv[2]!="Mu") ) correctusage=false;
  if(!correctusage){
    std::cout<<"Need to specify whether running on Data or MC and whether running for electrons or muons. The four possible ways of running are\n"
	     <<"./PromptRate.o Data El\n"
	     <<"./PromptRate.o Data Mu\n"
	     <<"./PromptRate.o MC El\n"
	     <<"./PromptRate.o MC Mu\n";
  }

  //get filename based on Data/MC
  std::string filename;
  if(argv[1]=="Data") filename="/eos/uscms/store/user/lpctlbsm/clint/Data/ljmet_tree_data.root";
  else filename="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_DYJets.root";

  //get channel based on El/Mu
  bool MuonChannel;
  if(argv[2]=="Mu") MuonChannel=true;
  else MuonChannel=false;

  return 0;
}
