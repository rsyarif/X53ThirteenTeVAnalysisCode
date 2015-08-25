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
#include <map>
#include <string>
#include <sstream> 
#include "../plugins/Macros.cc"

//helper functions
std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons);

//A script to get the prompt rate for electrons and muons. Usage is ./ChargeMisID.o <Data,MC> <El,Mu> 

int main(int argc, char* argv[]){

  if(argc!=3){
    std::cout<<"Need to specify whether running on Data or MC and whether 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns \n"
	     <<"./ChargeMisID.o Data 25ns \n"
	     <<"./ChargeMisID.o MC 50ns \n"
	     <<"./ChargeMisID.o MC 25ns \n";
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];

  bool correctusage=false;
  if(argc==2 && (argv1.find("Data")!=std::string::npos || argv1.find("MC")!=std::string::npos ) && (argv2=="25ns" || argv2=="50ns") ) correctusage=true;
  if(!correctusage){
    std::cout<<"Need to specify whether running on Data or MC and 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns \n"
	     <<"./ChargeMisID.o Data 25ns \n"
	     <<"./ChargeMisID.o MC 50ns \n"
	     <<"./ChargeMisID.o MC 25ns \n";
    return 0;
  }

  //get filename based on Data/MC
  std::string filename;
  bool data;
  bool FiftyNS;
  if(argv1=="Data" && argv2=="50ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Data/50ns/ljmet_tree_data.root"; data=true; FiftyNS=true}
  else  if(argv1=="Data" && argv2=="25ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Data/25ns/ljmet_tree_data.root"; data=true; FiftyNS=false;}
  else if(argv1=="MC" && argv2=="50ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Spring15/50ns/ljmet_trees/ljmet_DYJets.root"; data=false; FiftyNS=true;}
  else if(argv1=="MC" && argv2=="25ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/ljmet_trees/ljmet_DYJets.root"; data=false; FiftyNS=false;}
  else{
    std::cout<<"Need to specify whether running on Data or MC and 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns \n"
	     <<"./ChargeMisID.o Data 25ns \n"
	     <<"./ChargeMisID.o MC 50ns \n"
	     <<"./ChargeMisID.o MC 25ns \n";
  }

  //make filename for output root file
  std::string outname;
  if(data)outname="ChargeMisID_Data_Electrons.root"; 
  else outname="ChargeMisID_MC_Electrons.root"; 


  //open output file
  TFile* fout= new TFile(outname.c_str(),"RECREATE");

  //get tree reader to read in data
  TreeReader* tr= new TreeReader(filename.c_str());
  TTree* t=tr->tree;

  //initialize needed histograms
  TH1F* ptNumHist = new TH1F("ptNumHist","p_{T} of Tight Leptons",20,0,600);
  TH1F* ptDenHist = new TH1F("ptDenHist","p_{T} of All Leptons",20,0,600);
  TH1F* etaNumHist = new TH1F("etaNumHist","#eta of Tight Leptons",12,-5,5);
  TH1F* etaDenHist = new TH1F("etaDenHist","#eta of All Leptons",12,-5,5);

  //get number of entries and start event loop
  int nEntries = t->GetEntries();
  for(int ient=0; ient<nEntries; ient++){

    tr->GetEntry(ient);

    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    //make vector of leptons
    std::vector<TLepton*> leptons = makeLeptons(tr->allMuons,tr->allElectrons,MuonChannel);

    //check for at least one tight lepton
    bool oneTight=false;
    for(std::vector<TLepton*>::size_type ilep=0; ilep<leptons.size(); ilep++){
      if(leptons.at(ilep)->Tight){
	oneTight=true;
	break;
      }
    }

    //skip of not at least one tight and at least one other loose  
    if(!oneTight || leptons.size()<2) continue;

    //get pair of leptons closest to z mass;
    float zmass = 91.1;
    float massDiff=9999;
    TLepton* lep1=0;
    TLepton* lep2=0;
    float pairmass=-9999;
    for(std::vector<TLepton*>::size_type ilep=0; ilep<leptons.size(); ilep++){
      //loop over remaining leptons
      for(std::vector<TLepton*>::size_type jlep=ilep+1; jlep<leptons.size(); jlep++){
	pairmass = (leptons.at(ilep)->lv + leptons.at(jlep)->lv).M();
	if(fabs(zmass-pairmass)<massDiff){
	  massDiff = fabs(zmass-pairmass);
	  lep1=leptons.at(ilep);
	  lep2=leptons.at(jlep);
	}
      }//end second loop over leptons
    }//end loop over leptons

    //check that leptons are in Zpeak
    bool zpeak= massDiff<15 ? true : false;

    if(!zpeak) continue;

    //now fill histograms
    ptDenHist->Fill(lep2->pt);
    if(lep2->Tight) ptNumHist->Fill(lep2->pt);
    etaDenHist->Fill(lep2->eta);
    if(lep2->Tight) etaNumHist->Fill(lep2->eta);

  }//end event loop

  //write file now that histograms have been filled
  fout->WriteTObject(ptNumHist);
  fout->WriteTObject(ptDenHist);
  fout->WriteTObject(etaNumHist);
  fout->WriteTObject(etaDenHist);
  //make tgraphs for promptrate
  TGraphAsymmErrors* ptGraph = new TGraphAsymmErrors(ptNumHist,ptDenHist);
  TGraphAsymmErrors* etaGraph = new TGraphAsymmErrors(etaNumHist,etaDenHist);
  //write the tgraphs
  fout->WriteTObject(ptGraph);
  fout->WriteTObject(etaGraph);




  return 0;
}


std::vector<TLepton*> makeLeptons(std::vector<TElectron*> electrons){

  std::vector<TLepton*> Leptons;

  //fill with  electrons
  for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
    TElectron* iel = electrons.at(uiel);
    TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge);
    iLep->Tight=iel->cutBasedTight();
    iLep->Loose=iel->cutBasedLoose();
    iLep->isMu = false;
    iLep->isEl = true;
    //only save if at least loose
    if(iLep->Tight || iLep->Loose){
      //apply pt cut
      if(iLep->pt>30) Leptons.push_back(iLep);
    }
  }


  return Leptons;
 
}
