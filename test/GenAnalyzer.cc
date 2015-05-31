#include <iostream>
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "../interface/TreeReader.h"

void doGenPlots(TFile* outFile, TTree* t, TreeReader* tr){

  //change to top director then make directory for Gen Plots
  outFile->cd();
  TDirectory* genDir = outFile->mkdir("GenPlots");
  genDir->cd();

  //histograms
  TH1F* h_dilepMass = new TH1F("h_dilepMass","Same Sign Dilepton Mass", 25, 0, 1000);
  TH1F* h_GenHT = new TH1F("h_GenHT", "Gen H_{T}", 50, 500, 3000);
  //get number of entries
  int nEntries = t->GetEntries();

  //event loop
  for(int ient=0; ient<nEntries; ient++){
    tr->GetEntry(ient);
    //load in genparticles
    std::vector<TGenParticle*> genLeptons;
    //loop through and save if electron or muon
  
    for(unsigned int uigen=0; uigen < tr->genParticles.size(); uigen++){
      TGenParticle* p = tr->genParticles.at(uigen);
      if( (p->status==23 || p->status==1) && ( fabs(p->id)==13 || fabs(p->id)==11)) genLeptons.push_back(p);
    }


    //now check for same-sign
    bool samesign=false;
    std::vector<TGenParticle*> vSSGenLep;
    for(unsigned int uigen=0; uigen<genLeptons.size(); uigen++){
      for(unsigned int ujgen=uigen+1; ujgen<genLeptons.size(); ujgen++){
	if( genLeptons.at(uigen)->charge==genLeptons.at(ujgen)->charge){
	  samesign=true;
	  vSSGenLep.push_back(genLeptons.at(uigen));
	  vSSGenLep.push_back(genLeptons.at(ujgen));
	}
      }
    }//end check for samesign

    if(!samesign) continue;
    
    //save dilepmass
    TLorentzVector v1 = vSSGenLep.at(0)->lv;
    TLorentzVector v2 = vSSGenLep.at(1)->lv;

    h_dilepMass->Fill( (v1+v2).M() );


    //make Gen HT
    float HT=0;
    for(unsigned int ui=0; ui<tr->genJets.size(); ui++){
      HT+=tr->genJets.at(ui)->pt;
    }
    h_GenHT->Fill(HT);
  }//end event loop
  outFile->Write();
}

