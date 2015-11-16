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
TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles);

int main(int argc, char* argv[]){


  TH1F* h_dxy_np = new TH1F("h_dxy_np","dxy of non-prompt ttbar electrons",100,0,5);
  TH1F* h_dxy_pttb = new TH1F("h_dxy_pttb","dxy of prompt ttbar electrons",100,0,5);
  TH1F* h_dxy_lhsig = new TH1F("h_dxy_psig","dxy of prompt LH signal electrons",100,0,5);
  TH1F* h_dxy_rhsig = new TH1F("h_dxy_psig","dxy of prompt RH signal electrons",100,0,5);


  //ttbar tree reader
  TreeReader* tr_ttb = new TreeReader("ljmet_TTbar-powheg.root");
  //lh tree reader
  TreeReader* tr_lh = new TreeReader("ljmet_X53X53m700LH.root");

  //rh tree reader
  TreeReader* tr_rh = new TreeReader("ljmet_X53X53m700RH.root");

  
  int nEntries_ttb = tr_ttb->tree->GetEntries();
  int nEntries_lh = tr_lh->tree->GetEntries();
  int nEntries_rh = tr_rh->tree->GetEntries();


  for(int ient=0; ient < nEntries_ttb; ient++){

    tr_ttb->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries_ttb<<" events"<<std::endl;


  return 0;
}


TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles){


  TGenParticle* gp=0;

  bool nearbyEl = false;
  
  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    float drtemp = pow( pow( el->eta - genParticle->eta, 2 ) + pow( el->phi - genParticle->phi, 2), 0.5);
    //std::cout<<"gen particle "<<igen<< " of "<<genParticles.size()<<" with id: "<< genParticle->id<<" and status: "<<genParticle->status<<" and mother: "<<genParticle->motherId<<" and dR: "<<drtemp<<std::endl;
    if(drtemp < dR){
      dR = drtemp;
      gp=genParticle;
    }
    if(drtemp<0.1 && fabs(genParticle->id)==11 && genParticle->status==1) nearbyEl=true;
  }

  if( !nearbyEl) return gp; //return the closest particle unless there is a nearby final state electron
  else{//run through again and only check electrons
    //reset dR
    dR=999;
    //std::cout<<"nearby electron"<<std::endl;
    for(unsigned int igen=0; igen<genParticles.size(); igen++){
      TGenParticle* genParticle = genParticles.at(igen);
      if(fabs(genParticle->id)!=11 || genParticle->status!=1) continue; //only check final state electrons
      float drtemp = pow( pow( el->eta - genParticle->eta, 2 ) + pow( el->phi - genParticle->phi, 2), 0.5);      
      if(drtemp < dR){
	dR = drtemp;
	gp=genParticle;
      }
    }//end loop over gen electrons
  
  }

  return gp;

}
