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
#include <algorithm>
#include "../plugins/Macros.cc"

//helper functions
std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons, bool mc, bool FiftyNs);

bool sortByPhi(TLepton* lep1, TLepton* lep2){return lep1->phi > lep2->phi;};
//A script to get the prompt rate for electrons and muons. Usage is ./PromptRate.o <Data,MC> <El,Mu> 

int main(int argc, char* argv[]){

  if(argc!=3){
    std::cout<<"Need to specify whether running on Data or MC and whether running for electrons or muons. The four possible ways of running are\n"
	     <<"./PromptRate.o Data El\n"
	     <<"./PromptRate.o Data Mu\n"
	     <<"./PromptRate.o MC El\n"
	     <<"./PromptRate.o MC Mu\n";
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];

  bool correctusage=false;
  if(argc==3 && (argv1.find("Data")!=std::string::npos || argv1.find("MC")!=std::string::npos ) && (argv2.find("El")!=std::string::npos || argv2.find("Mu")!=std::string::npos)  ) correctusage=true;
  if(!correctusage){
    std::cout<<"Need to specify whether running on Data or MC and whether running for electrons or muons. The four possible ways of running are\n"
	     <<"./PromptRate.o Data El\n"
	     <<"./PromptRate.o Data Mu\n"
	     <<"./PromptRate.o MC El\n"
	     <<"./PromptRate.o MC Mu\n";
  }

  //get filename based on Data/MC
  std::string filename;
  bool data;
  if(argv1=="Data") {filename="/eos/uscms/store/user/lpctlbsm/clint/Run2015B/ljmet_trees/ljmet_Data_All.root"; data=true;}
  else {filename="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/ljmet_trees/ljmet_DYJets_LooseIDLepJetCleaning.root"; data=false;}
  bool FiftyNs=data;
  //get channel based on El/Mu
  bool MuonChannel;
  if(argv2=="Mu") MuonChannel=true;
  else MuonChannel=false;

  //make filename for output root file
  std::string outname;
  if(MuonChannel){
    if(data)outname="PromptRate_Data_Run2015B_Muons_SortByPhi.root"; 
    else outname="PromptRate_MC_Muons_SortByPhi.root"; 
  }
  else{
    if(data)outname="PromptRate_Data_Run2015B_Electrons_SortByPhi.root"; 
    else outname="PromptRate_MC_Electrons_SortByPhi.root"; 
  }

  //open output file
  TFile* fout= new TFile(outname.c_str(),"RECREATE");

  //get tree reader to read in data
  TreeReader* tr= new TreeReader(filename.c_str(),!data);
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

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    //make vector of leptons
    std::vector<TLepton*> leptons = makeLeptons(tr->allMuons,tr->allElectrons,MuonChannel,!data,FiftyNs);

    //check for at least one tight lepton
    bool oneTight=false;
    for(std::vector<TLepton*>::size_type ilep=0; ilep<leptons.size(); ilep++){
      if(leptons.at(ilep)->Tight){
	oneTight=true;
	break;
      }
    }

    //skip if not at least one tight and at least one other loose  
    if(!oneTight || leptons.size()<2) continue;

    //get pair of leptons closest to z mass;
    float zmass = 91.1;
    float massDiff=9999;
    TLepton* lep1;
    TLepton* lep2;
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

    //now sort leptons based on phi (i.e. quasi-randomly)
    std::vector<TLepton*> leps; leps.push_back(lep1); leps.push_back(lep2);
    std::sort(leps.begin(),leps.end(),sortByPhi);

    /* //revert to Aram's method
    ptDenHist->Fill(0);
    if(leps.at(0)->Tight && leps.at(1)->Tight) ptNumHist->Fill(0);
    etaDenHist->Fill(0);
    if(leps.at(0)->Tight && leps.at(1)->Tight) etaNumHist->Fill(0);*/
    
    //now fill histograms
    ptDenHist->Fill(leps.at(0)->pt);
    if(leps.at(0)->Tight) ptNumHist->Fill(leps.at(0)->pt);
    etaDenHist->Fill(leps.at(0)->eta);
    if(leps.at(0)->Tight) etaNumHist->Fill(leps.at(0)->eta);

  }//end event loop

  std::cout<<"Mean of num pt hist is: "<<ptNumHist->GetMean()<<std::endl;
  std::cout<<"Mean of den pt hist is: "<<ptDenHist->GetMean()<<std::endl;
  std::cout<<"Mean of num eta hist is: "<<etaNumHist->GetMean()<<std::endl;
  std::cout<<"Mean of den eta hist is: "<<etaDenHist->GetMean()<<std::endl;

  //make tgraphs for promptrate
  TGraphAsymmErrors* ptGraph = new TGraphAsymmErrors(ptNumHist,ptDenHist);
  TGraphAsymmErrors* etaGraph = new TGraphAsymmErrors(etaNumHist,etaDenHist);
  //append everything to output file
  fout->Append(ptNumHist);
  fout->Append(ptDenHist);
  fout->Append(etaNumHist);
  fout->Append(etaDenHist);
  fout->Append(ptGraph);
  fout->Append(etaGraph);
  fout->Write();


  return 0;
}


std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons,bool mc, bool FiftyNs){

  std::vector<TLepton*> Leptons;

  if(Muons){
    //fill with  muons
    for(unsigned int uimu=0; uimu<muons.size(); uimu++){
      TMuon* imu = muons.at(uimu);
      TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);
      iLep->Tight=imu->cutBasedTight();
      iLep->Loose=imu->cutBasedLoose();
      iLep->isMu = true;
      iLep->isEl = false;
      //only save if at least loose
      if(iLep->Tight || iLep->Loose){
	//apply pt cut
	if(iLep->pt>30) Leptons.push_back(iLep);
      }
    }
  }

  else{
    //fill with  electrons
    for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
      TElectron* iel = electrons.at(uiel);
      TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge);


      if(mc){
	if(FiftyNs){
	  iLep->Tight=iel->cutBasedTight();
	  iLep->Loose=iel->cutBasedLoose();
	}
	else{
	  iLep->Tight=iel->cutBasedTight25nsSpring15MC();
	  iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
	}
      }
      else{
	iLep->Tight=iel->cutBasedTight();
	iLep->Loose=iel->cutBasedLoose();
      }
      
      iLep->isMu = false;
      iLep->isEl = true;
      //only save if at least loose
      if(iLep->Tight || iLep->Loose){
	//apply pt cut
	if(iLep->pt>30) Leptons.push_back(iLep);
      }
    }
  }

  return Leptons;

}
