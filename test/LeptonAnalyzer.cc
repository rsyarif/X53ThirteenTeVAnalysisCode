#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "TDirectory.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include "TString.h"

const double M_EL = 0.000510998928; //Mass of electron in GeV
const double M_MU = 0.1056583715;   //Mass of muon in GeV
const double M_Z  = 91.1876;        //Mass of Z boson
const double dM   = 15;             //Size of window around Z

bool matchToGenLep(TMuon* mu, std::vector<TGenParticle*> genParticles);
bool matchToGenLep(TElectron* el, std::vector<TGenParticle*> genParticles);
void doMuCutFlow(TH1F*& h, TMuon* mu);
void doElCutFlow(TH1F*& h, TElectron* el);

int main(int argc, char* argv[]){

  //read in arguments
  std::string argv1(argv[1]);
  bool data;
  if(argv1.find("Data")!=std::string::npos) data=true;
  else data=false;

  std::string chirality(argv[2]);
  std::string mass(argv[3]);

  TString filename;
  if(data) filename = "/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Oct06/ljmet_trees/ljmet_Data_All.root";
  else filename = "/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct06/ljmet_trees/ljmet_X53X53m"+mass+chirality+".root";

  //load in tree reader
  TreeReader* tr = new TreeReader(filename,!data);
  TTree* t = tr->tree;
  int nEntries = t->GetEntries();

  //counter for number of loose muons
  float nLooseMuons=0;

  //outfile
  std::string outname;
  if(data)outname="LeptonEfficiency_Signal_Data_Run2015D.root"; 
  else outname="LeptonEfficiency_Signal_MC_"+mass+"_"+chirality+".root"; 
  TFile* fout = new TFile(outname.c_str(),"RECREATE");

  //setup histograms
  TH1F* h_MuCutFlow = new TH1F("h_MuCutFlow","Muon Cut Flow",12,0,12);
  TH1F* hPtNum_Mu = new TH1F("hPtNum_Mu","p_{T} of Tight Muons",60,0,600);
  TH1F* hPtDen_Mu = new TH1F("hPtDen_Mu","p_{T} of Loose Muons",60,0,600);
  TH1F* hEtaNum_Mu = new TH1F("hEtaNum_Mu","#eta of Tight Muons",15,-3,3);
  TH1F* hEtaDen_Mu = new TH1F("hEtaDen_Mu","#eta of Loose Muons",15,-3,3);

  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    tr->GetEntry(ient);
    
    //only do muon cut flow if either cross trigger of one of muon triggers fired
    bool MuTrigFire = false;
    if( tr->HLT_Mu8Ele23 || tr->HLT_Mu23Ele12 || tr->HLT_Mu8Ele17 || tr->HLT_Mu17Ele12 || tr->HLT_Mu30Ele30 || tr->HLT_Mu27TkMu8 || tr->HLT_Mu30TkMu11 || tr->HLT_Mu40TkMu11) MuTrigFire=true;

    if(MuTrigFire){
      for(std::vector<TMuon*>::size_type imu=0; imu<tr->looseMuons.size();imu++){
	//increment to total number of loose muons so we can scale hist correctly at the end
	nLooseMuons+=1;
	//get muon
	TMuon* mu = tr->looseMuons.at(imu);
	//make sure muon is matched to a gen muon
	bool matched = matchToGenLep(mu,tr->genParticles);
	if(!matched) continue;
	//make pt and eta efficiency plots
	hPtDen_Mu->Fill(mu->pt);
	hEtaDen_Mu->Fill(mu->eta);
	if(mu->cutBasedTight()){
	  hPtNum_Mu->Fill(mu->pt);
	  hEtaNum_Mu->Fill(mu->eta);
	}
	//now do cutflow
	doMuCutFlow(h_MuCutFlow, mu);
      }
    }//end check of muon trigger firing

  }//end event loop
  
  h_MuCutFlow->Scale( 1 / nLooseMuons);

  //print out efficiency
  std::cout<<"Efficiency for >30 GeV Loose Muons from "<<mass<<" GeV X53 becoming tight: "<<h_MuCutFlow->GetBinContent(11)<<std::endl;
  std::cout<<"Efficiency for >40 GeV Loose Muons from "<<mass<<" GeV X53 becoming tight: "<<h_MuCutFlow->GetBinContent(12)<<std::endl;

  fout->Append(h_MuCutFlow);
  fout->Append(hPtNum_Mu);
  fout->Append(hPtDen_Mu);
  fout->Append(hEtaNum_Mu);
  fout->Append(hEtaDen_Mu);
  std::cout<<"appended everything"<<std::endl;
  fout->Write();

  return 0;
}
 
void doMuCutFlow(TH1F*& hist, TMuon* mu){

  if(mu->Global) hist->AddBinContent(1);
  if(mu->pt>30) hist->AddBinContent(2);
  if(mu->eta<2.4)hist->AddBinContent(3) ;
  if(mu->chi2 < 10) hist->AddBinContent(4);
  if(mu->dz<0.5) hist->AddBinContent(5);
  if(mu->dxy<0.2) hist->AddBinContent(6);
  if(mu->nValMuHits > 1 ) hist->AddBinContent(7);
  if(mu->nMatchedStations>2) hist->AddBinContent(8);
  if(mu->nValPixelHits > 1) hist->AddBinContent(9);
  if(mu->nTrackerLayers>6) hist->AddBinContent(10);
  if(mu->relIso>0.06) hist->AddBinContent(11);
  if(mu->pt>40) hist->AddBinContent(12);

}


bool matchToGenLep(TMuon* mu, std::vector<TGenParticle*> genParticles){

  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    //only run over muons from hard scattering
    if( ! (fabs(genParticle->id)==13) ) continue;
    if( ! (genParticle->status==23 || genParticle->status==1) ) continue;

    float drtemp = pow( pow( mu->eta - genParticle->eta, 2 ) + pow( mu->phi - genParticle->phi, 2), 0.5);
    if(drtemp < dR){
      dR = drtemp;
    }
  }

  //now we have a min deltaR between our muon and all muons from hard scattering, if it is less than 0.15 let's consider it matched
  if(dR <0.1) return true;
  else return false;
  
}
    
