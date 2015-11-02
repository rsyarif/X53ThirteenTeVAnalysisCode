#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <map>
#include <string>
#include <sstream> 
#include "../plugins/Macros.cc"

//helper functions
std::vector<TLepton*> makeLeptons(std::vector<TElectron*> electrons, std::string ID);
bool matchToGenLep(TElectron* el, std::vector<TGenParticle*> genParticles);
TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles);


int main(int argc, char* argv){

  if(argc!=4){
    std::cout<<"Need to specify electrons or muons and ID used! Exiting..."<<std::endl;
    return 0; 
  }

  bool Muons;
  std::string channel(argv[1]);
  if(channel=="Muons") Muons=true;
  else Muons=false;

  std::string elID(argv[2]);
  std::string muID(argv[3]);

  bool mc=true;
  
  TreeReader* tr = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/ObjectReview/ljmet_trees/ljmet_TTJets.root");
  TTree* t = tr->tree;


  TH1F* elNumHist_lpt = new TH1F("elNumHist_lpt","elNumHist_lpt",10,0,10);
  TH1F* elDenHist_lpt = new TH1F("elDenHist_lpt","elDenHist_lpt",10,0,10);
  TH1F* elNumHist_hpt = new TH1F("elNumHist_hpt","elNumHist_hpt",10,0,10);
  TH1F* elDenHist_hpt = new TH1F("elDenHist_hpt","elDenHist_hpt",10,0,10);
  TH1F* elNumHist_all = new TH1F("elNumHist_all","elNumHist_all",10,0,10);
  TH1F* elDenHist_all = new TH1F("elDenHist_all","elDenHist_all",10,0,10);

  TH1F* muNumHist_lpt = new TH1F("muNumHist_lpt","muNumHist_lpt",10,0,10);
  TH1F* muDenHist_lpt = new TH1F("muDenHist_lpt","muDenHist_lpt",10,0,10);
  TH1F* muNumHist_hpt = new TH1F("muNumHist_hpt","muNumHist_hpt",10,0,10);
  TH1F* muDenHist_hpt = new TH1F("muDenHist_hpt","muDenHist_hpt",10,0,10);
  TH1F* muNumHist_all = new TH1F("muNumHist_all","muNumHist_all",10,0,10);
  TH1F* muDenHist_all = new TH1F("muDenHist_all","muDenHist_all",10,0,10);


  int nEntries = t->GetEntries();

  for(int ient=0; ient < nEntries; ient++){

    tr->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    std::vector<TElectron*> electrons = tr->AllElectrons;

    for(unsigned int i=0; i<electrons.size();i++){
      TElectron* iel = electrons.at(i);
      bool loose = false;
      bool tight = false;
      if(eldID=="MVATightRC"){
	loose = iel->MVALooseRC;
	tight = iel->MVATightRC;
      }
      else{
	std::cout<<"Didn't pick analysis ID! Are you sure? Exiting so you can think about it..."<<std::endl;
	return 0;
      }

      if(loose){
	//make sure it is not matched to a gen electron
	bool matched = matchToGenLep(iel, tr->genParticles);
	if(matched) continue;

	if(iel->pt>25){ //only do at least 25 GeV pt leptons
	  if(iel->pt<35){ //save ones in window used in data
	    elDenHist_lpt->Fill(0);
	    if(tight) elNumHist_lpt->Fill(0);
	  }
	  else{ //higher pt regime
	    elDenHist_hpt->Fill(0);
	    if(tight) elNumHist_hpt->Fill(0);
	  }
	    
      }

    }//electron loop

  }

  return 0;

}

bool matchToGenLep(TElectron* el, std::vector<TGenParticle*> genParticles){

  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    //only run over electrons from hard scattering
    if( ! (fabs(genParticle->id)==11) ) continue;
    if( ! (genParticle->status==23 || genParticle->status==1) ) continue;

    float drtemp = pow( pow( el->eta - genParticle->eta, 2 ) + pow( el->phi - genParticle->phi, 2), 0.5);
    if(drtemp < dR){
      dR = drtemp;
    }
  }

  //now we have a min deltaR between our electron and all electrons from hard scattering, if it is less than 0.15 let's consider it matched
  if(dR <0.1) return true;
  else return false;
  
}
