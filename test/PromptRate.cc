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
TLepton* makeTagLepton(std::vector<TMuon*> muons,std::vector<TElectron*> electrons,bool Muons,bool mc,bool FiftyNs,std::string ID);
std::vector<TLepton*> makeProbeLeptons(TLepton* tag, std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons, bool mc, bool FiftyNs, std::string ID);
bool sortByPhi(TLepton* lep1, TLepton* lep2){return lep1->phi > lep2->phi;};

//A script to get the prompt rate for electrons and muons. Usage is ./PromptRate.o <Data,MC> <El,Mu> 

int main(int argc, char* argv[]){

  if(argc!=4){
    std::cout<<"Need to specify whether running on Data or MC and whether running for electrons or muons as well as the ID used. The four possible ways of running are\n"
	     <<"./PromptRate.o Data El ID\n"
	     <<"./PromptRate.o Data Mu ID\n"
	     <<"./PromptRate.o MC El ID\n"
	     <<"./PromptRate.o MC Mu ID\n\n";
    std::cout<<"The IDs for electrons are: CBTight, CBLoose, MVATight, MVALoose. The IDS for muons are: CBTight, CBLoose."<<std::endl;
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];
  std::string ID = argv[3];

  bool correctusage=false;
  if(argc==4 && (argv1.find("Data")!=std::string::npos || argv1.find("MC")!=std::string::npos ) && (argv2.find("El")!=std::string::npos || argv2.find("Mu")!=std::string::npos)  ) correctusage=true;
  if(!correctusage){
    std::cout<<"Need to specify whether running on Data or MC and whether running for electrons or muons. The four possible ways of running are\n"
	     <<"./PromptRate.o Data El\n"
	     <<"./PromptRate.o Data Mu\n"
	     <<"./PromptRate.o MC El\n"
	     <<"./PromptRate.o MC Mu\n";
    return 0;
  }

  //get filename based on Data/MC
  std::string filename;
  bool data;
  if(argv1=="Data") {filename="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Oct08/ljmet_trees/ljmet_Data_All.root"; data=true;}
  else {filename="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct06/ljmet_trees/ljmet_DYJets.root"; data=false;}
  bool FiftyNs=data;
  //get channel based on El/Mu
  bool MuonChannel;
  if(argv2=="Mu") MuonChannel=true;
  else MuonChannel=false;

  //make filename for output root file
  std::string outname;
  if(MuonChannel){
    if(data)outname="PromptRate_Data_Run2015D_Muons_"+ID+"_SortByPhi.root"; 
    else outname="PromptRate_MC_Muons_"+ID+"_SortByPhi.root"; 
  }
  else{
    if(data)outname="PromptRate_Data_Run2015D_Electrons_"+ID+"_SortByPhi.root"; 
    else outname="PromptRate_MC_Electrons_"+ID+"_SortByPhi.root"; 
  }

  //open output file
  TFile* fout= new TFile(outname.c_str(),"RECREATE");

  //get tree reader to read in data
  TreeReader* tr= new TreeReader(filename.c_str(),!data);
  TTree* t=tr->tree;

  //initialize needed histograms
  TH1F* ptNumHist_Aram = new TH1F("ptNumHist_Aram","p_{T} of Tight Leptons",20,0,600);
  TH1F* ptDenHist_Aram = new TH1F("ptDenHist_Aram","p_{T} of Loose Leptons",20,0,600);
  TH1F* etaNumHist_Aram = new TH1F("etaNumHist_Aram","#eta of Tight Leptons",12,-5,5);
  TH1F* etaDenHist_Aram = new TH1F("etaDenHist_Aram","#eta of Loose Leptons",12,-5,5);

  //initialize needed histograms
  TH1F* ptNumHist = new TH1F("ptNumHist","p_{T} of Tight Leptons",20,0,600);
  TH1F* ptDenHist = new TH1F("ptDenHist","p_{T} of Loose Leptons",20,0,600);
  TH1F* etaNumHist = new TH1F("etaNumHist","#eta of Tight Leptons",12,-5,5);
  TH1F* etaDenHist = new TH1F("etaDenHist","#eta of Loose Leptons",12,-5,5);

  TH1F* pairMassHist_pass = new TH1F("pairMassHist_pass","Best Pair Mass Passing Probe",40,50,130);
  TH1F* pairMassHist_fail = new TH1F("pairMassHist_fail","Best Pair Mass Failing Probe",40,50,130);
  TH1F* pairMassHist_all = new TH1F("pairMassHist_all","Best Pair Mass All Probes",40,50,130);

  //get number of entries and start event loop
  int nEntries = t->GetEntries();
  for(int ient=0; ient<nEntries; ient++){

    tr->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    //make tag lepton
    TLepton* tagLepton = makeTagLepton(tr->allMuons,tr->allElectrons,MuonChannel,!data,FiftyNs, ID);
    //if no tag lepton found in the event a dummy is returned with pt==-999 so skip event if it is this value (i.e. if no tag lepton found in event)
    if(tagLepton->pt==-999) continue;
    std::vector<TLepton*> probeLeptons = makeProbeLeptons(tr->allMuons,tr->allElectrons,MuonChannel,!data,FiftyNs, ID);

    std::vector<TLepton*> leptons = findBestPair(tagLepton,probeLeptons); //only returns two leptons if a pair is found within z window
    if(leptons.size()!=2) continue; //skip if no good pair found

    //get pair mass
    float pairMass = (leptons.at(0)->lv + leptons.at(1)).M();
    pairMassHist_all->Fill(pairMass);

    //revert to Aram's method
    ptDenHist_Aram->Fill(0);
    if(leptons.at(0)->Tight && leptons.at(1)->Tight) ptNumHist_Aram->Fill(0);
    etaDenHist_Aram->Fill(0);
    if(leptons.at(0)->Tight && leptons.at(1)->Tight) etaNumHist_Aram->Fill(0);
    

    //now fill histograms, tag lepton will always be first so get element 1 for probe
    ptDenHist->Fill(leptons.at(1)->pt);
    if(leptons.at(1)->Tight){
      ptNumHist->Fill(leptons.at(1)->pt);
      pairMassHist_pass->Fill(pairMass);
    }
    else pairMassHist_fail->Fill(pairMass);
    etaDenHist->Fill(leptons.at(1)->eta);
    if(leptons.at(1)->Tight) etaNumHist->Fill(leptons.at(1)->eta);

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
  fout->Append(ptNumHist_Aram);
  fout->Append(ptDenHist_Aram);
  fout->Append(etaNumHist_Aram);
  fout->Append(etaDenHist_Aram);
  fout->Append(ptGraph);
  fout->Append(etaGraph);
  fout->Write();


  return 0;
}


std::vector<TLepton*> makeProbeLeptons(TLepton* tag, std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons,bool mc, bool FiftyNs, std::string ID){

  std::vector<TLepton*> Leptons;

  if(Muons){
    //fill with  muons
    for(unsigned int uimu=0; uimu<muons.size(); uimu++){
      TMuon* imu = muons.at(uimu);
      TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);
      //skip if same as tag
      if(imu->pt==tag->pt && imu->eta==tag->eta && imu->phi==tag->eta) continue
      if(ID=="CBTight"){
	iLep->Tight=imu->cutBasedTight();
	iLep->Loose=imu->cutBasedLoose();
      }
      else if(ID=="CBLoose"){
	iLep->Tight=imu->cutBasedLoose();
	iLep->Loose=true; //in case 'loose ID' is specified as 'tight', take any muon as loose ID
      }
      iLep->isMu = true;
      iLep->isEl = false;
      //only save if at least loose
      if(iLep->Loose){
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
      //skip if same as tag
      if(iel->pt==tag->pt && iel->eta==tag->eta && iel->phi==tag->eta) continue
      if(ID=="CBTight"){
	iLep->Tight=iel->cutBasedTight25nsSpring15MC();
	iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
      }
      else if(ID=="CBLoose"){
	iLep->Tight=iel->cutBasedLoose25nsSpring15MC();
	iLep->Loose=true;
      }
      else if(ID=="MVATight"){
	iLep->Tight=iel->mvaTightIso();
	iLep->Loose=iel->mvaLooseIso();
      }
      else if(ID=="MVATightNoIso"){
	iLep->Tight=iel->mvaTight();
	iLep->Loose=iel->mvaLoose();
      }
      else if(ID=="MVALoose"){
	iLep->Tight=iel->mvaLooseIso();
	iLep->Loose=true;
      }
      else if(ID=="MVALooseNoIso"){
	iLep->Tight=iel->mvaLoose();
	iLep->Loose=true;
      }
      
      iLep->isMu = false;
      iLep->isEl = true;
      //save if loose
      if(iLep->Loose){
	//apply pt cut
	if(iLep->pt>30) Leptons.push_back(iLep);
      }
    }
  }

  return Leptons;

}

std::vector<TLepton*> findBestPair(TLepton* tag, std::vector<TLeptons*> probes){

  std::vector<TLepton*> leps;

  //get pair of leptons closest to z mass;
  float zmass = 91.1;
  float massDiff=9999;
  float pairmass=-9999;

  int index = 0;
  int dummy = 0;

  for(std::vector<TLepton*>::size_type jlep=0; jlep<probes.size(); jlep++){
	pairmass = (tag->lv + probes.at(jlep)->lv).M();
	if(fabs(zmass-pairmass)<massDiff){
	  massDiff = fabs(zmass-pairmass);
	  index=dummy;
	}
	//iterate dummy index
	dummy++;
    }//end loop over probes
  
  
  //check that leptons are in Zpeak
  bool zpeak= massDiff<15 ? true : false;

  TLepton* probe = probes.at(index);
  
  if(zpeak){
    leps.push_pack(tag);leps.push_back(probe);
  }
  
  return leps;

}

TLepton* makeTagLepton(std::vector<TMuon*> muons,std::vector<TElectron*> electrons,bool Muons,bool mc,bool FiftyNs,std::string ID){
    
  std::vector<TLepton*> Leptons;

  if(Muons){
    //fill with  muons
    for(unsigned int uimu=0; uimu<muons.size(); uimu++){
      TMuon* imu = muons.at(uimu);
      TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);
      if(ID=="CBTight"){
	iLep->Tight=imu->cutBasedTight();
	iLep->Loose=imu->cutBasedLoose();
      }
      else if(ID=="CBLoose"){
	iLep->Tight=imu->cutBasedLoose();
	iLep->Loose=true; //in case 'loose ID' is specified as 'tight', take any muon as loose ID
      }
      iLep->isMu = true;
      iLep->isEl = false;
      //only save if tight
      if(iLep->Tight){
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

      if(ID=="CBTight"){
	iLep->Tight=iel->cutBasedTight25nsSpring15MC();
	iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
      }
      else if(ID=="CBLoose"){
	iLep->Tight=iel->cutBasedLoose25nsSpring15MC();
	iLep->Loose=true;
      }
      else if(ID=="MVATight"){
	iLep->Tight=iel->mvaTightIso();
	iLep->Loose=iel->mvaLooseIso();
      }
      else if(ID=="MVATightNoIso"){
	iLep->Tight=iel->mvaTight();
	iLep->Loose=iel->mvaLoose();
      }
      else if(ID=="MVALoose"){
	iLep->Tight=iel->mvaLooseIso();
	iLep->Loose=true;
      }
      else if(ID=="MVALooseNoIso"){
	iLep->Tight=iel->mvaLoose();
	iLep->Loose=true;
      }
      
      iLep->isMu = false;
      iLep->isEl = true;
      //only save if tight
      if(iLep->Tight){
	//apply pt cut
	if(iLep->pt>30) Leptons.push_back(iLep);
      }
    }
  }

  //make sure there is at least one tight lepton in the event or return dummy
  TLepton* dummy = new TLepton(-999,-999,-999,-999,-999);
  if(Leptons.size()==0) return dummy;

  //if at least one tight sort the leptons by phi
  std::sort(leptons.begin(),leptons.end(),sortByPhi);
  //return the leading-in-phi lepton
  TLepton* tag = Leptons.at(0);
  return tag;
  
 
}
