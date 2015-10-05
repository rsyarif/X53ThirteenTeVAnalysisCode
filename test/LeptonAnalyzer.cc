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

const double M_EL = 0.000510998928; //Mass of electron in GeV
const double M_MU = 0.1056583715;   //Mass of muon in GeV
const double M_Z  = 91.1876;        //Mass of Z boson
const double dM   = 15;             //Size of window around Z

void doMuonCutFlow(TFile* outFile, TTree* t, TreeReader* tr){

  //for safety change to top directory
  outFile->cd();
  TDirectory *muDir = outFile->mkdir("MuCutFlow");
  muDir->cd();

  //histograms for muon variables
  TH1F* MatchedMu_Global= new TH1F("MatchedMu_Global","global of loose OR tight muons in same-sign events",2,0,2);
  TH1F* MatchedMu_PF= new TH1F("MatchedMu_PF","PF of loose OR tight muons in same-sign events",2,0,2);
  TH1F* MatchedMu_Pt= new TH1F("MatchedMu_Pt","p_{T} of loose OR tight muons in same-sign events",100,0,500);
  TH1F* MatchedMu_Eta= new TH1F("MatchedMu_Eta","#eta of loose OR tight muons in same-sign events",25,-5,5);
  TH1F* MatchedMu_Chi2= new TH1F("MatchedMu_Chi2","#chi^{2} of loose OR tight muons in same-sign events",100,0,10);
  TH1F* MatchedMu_dz= new TH1F("MatchedMu_dz","DZ of loose OR tight muons in same-sign events",50,0,1);
  TH1F* MatchedMu_dxy= new TH1F("MatchedMu_dxy","DXY of loose OR tight muons in same-sign events",50,0,1);
  TH1F* MatchedMu_nValMuHits= new TH1F("MatchedMu_nValMuHits","N_{ValidHits} of loose OR tight muons in same-sign events",20,0,20);
  TH1F* MatchedMu_nMatchedStations= new TH1F("MatchedMu_nMatchedStations","N_{MatchedStations}of loose OR tight muons in same-sign events",20,0,20);
  TH1F* MatchedMu_nValPixelHits= new TH1F("MatchedMu_nValPixelHits","N_{ValidPixelHits} of loose OR tight muons in same-sign events",20,0,20);
  TH1F* MatchedMu_relIso= new TH1F("MatchedMu_relIso","RelIso of loose OR tight muons in same-sign events",500,0,10);
  TH1F* MatchedMu_nTrackerLayers= new TH1F("MatchedMu_nTrackerLayers","N_{TrackLayers} of loose OR tight muons in same-sign events",20,0,20);

  double nAllMatchedMu =0;
  double nMatchedMuGlobalCut = 0;
  double nMatchedMuPFCut=0;
  double nMatchedMuPtCut=0;
  double nMatchedMuEtaCut=0;
  double nMatchedMuChi2Cut=0;
  double nMatchedMudZCut=0;
  double nMatchedMudXYCut=0;
  double nMatchedMuNValMuHitsCut=0;
  double nMatchedMuNMatchedStationsCut=0;
  double nMatchedMuNValPixHitsCut=0;
  double nMatchedMuNTrackLayersCut=0;
  double nMatchedMuRelIsoCut=0;

  TH1F* MatchedMuSS_Global= new TH1F("MatchedMuSS_Global","global of loose OR tight muons in same-sign events",2,0,2);
  TH1F* MatchedMuSS_PF= new TH1F("MatchedMuSS_PF","PF of loose OR tight muons in same-sign events",2,0,2);
  TH1F* MatchedMuSS_Pt= new TH1F("MatchedMuSS_pt","p_{T} of loose OR tight muons in same-sign events",100,0,500);
  TH1F* MatchedMuSS_Eta= new TH1F("MatchedMuSS_eta","#eta of loose OR tight muons in same-sign events",25,-5,5);
  TH1F* MatchedMuSS_Chi2= new TH1F("MatchedMuSS_chi2","#chi^{2} of loose OR tight muons in same-sign events",100,0,10);
  TH1F* MatchedMuSS_dz= new TH1F("MatchedMuSS_dz","DZ of loose OR tight muons in same-sign events",50,0,1);
  TH1F* MatchedMuSS_dxy= new TH1F("MatchedMuSS_dxy","DXY of loose OR tight muons in same-sign events",50,0,1);
  TH1F* MatchedMuSS_nValMuHits= new TH1F("MatchedMuSS_nValMuHits","N_{ValidHits} of loose OR tight muons in same-sign events",20,0,20);
  TH1F* MatchedMuSS_nMatchedStations= new TH1F("MatchedMuSS_nMatchedStations","N_{MatchedStations}of loose OR tight muons in same-sign events",20,0,20);
  TH1F* MatchedMuSS_nValPixelHits= new TH1F("MatchedMuSS_nValPixelHits","N_{ValidPixelHits} of loose OR tight muons in same-sign events",20,0,20);
  TH1F* MatchedMuSS_relIso= new TH1F("MatchedMuSS_relIso","RelIso of loose OR tight muons in same-sign events",500,0,10);
  TH1F* MatchedMuSS_nTrackerLayers= new TH1F("MatchedMuSS_nTrackerLayers","N_{TrackLayers} of loose OR tight muons in same-sign events",20,0,20);
  
  double nAllMatchedMuSS =0;
  double nMatchedMuSSGlobalCut = 0;
  double nMatchedMuSSPFCut=0;
  double nMatchedMuSSPtCut=0;
  double nMatchedMuSSEtaCut=0;
  double nMatchedMuSSChi2Cut=0;
  double nMatchedMuSSdZCut=0;
  double nMatchedMuSSdXYCut=0;
  double nMatchedMuSSNValMuHitsCut=0;
  double nMatchedMuSSNMatchedStationsCut=0;
  double nMatchedMuSSNValPixHitsCut=0;
  double nMatchedMuSSNTrackLayersCut=0;
  double nMatchedMuSSRelIsoCut=0;

  
  int nEntries = t->GetEntries();

  int nMuMu = 0;
  int nElEl = 0;
  int nElMu = 0;
  int nRecoMuMu = 0;

  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    tr->GetEntry(ient);
    

    /* FIRST DO CUT FLOW FOR ALL MUONS MATCHED TO A MUON FROM THE HARD SCATTERING*/

    //match muons to status three leptons
    std::vector<TMuon*> matchedMuons;
    for(unsigned int imu=0; imu< tr->allMuons.size(); imu++){
      float dR=100;


      //run through gen particle collection:
      for(unsigned int igen=0; igen<tr->genParticles.size(); igen++){
	//only run over muons from hard scattering
	if(!( ( fabs(tr->genParticles.at(igen)->id)==13) && (tr->genParticles.at(igen)->status==23 || tr->genParticles.at(igen)->status==1)) ) continue;
	float drtemp = pow( pow( tr->allMuons.at(imu)->eta - tr->genParticles.at(igen)->eta, 2 ) + pow( tr->allMuons.at(imu)->phi - tr->genParticles.at(igen)->phi, 2), 0.5);
	if(drtemp < dR){
	  dR = drtemp;
	}
      }

      //now we have a min deltaR between our muon and all muons from hard scattering, if it is less than 0.15 let's consider it matched
      if(dR <0.15){
	matchedMuons.push_back(tr->allMuons.at(imu));
      }
    }
    

    //now that we have our vector of matched mouns we can do a cut flow for them

    for(unsigned int imu=0; imu< matchedMuons.size(); imu++){
      //skip if not at least a loose muon
      if(! matchedMuons.at(imu)->cutBasedLoose() ) continue;
      nAllMatchedMu+=1;
      MatchedMu_Global->Fill(matchedMuons.at(imu)->Global);
      if(! matchedMuons.at(imu)->Global) continue;
      nMatchedMuGlobalCut+=1;
      MatchedMu_PF->Fill(matchedMuons.at(imu)->PFMuon);
      if(! matchedMuons.at(imu)->PFMuon) continue;
      nMatchedMuPFCut+=1;
      MatchedMu_Pt->Fill(matchedMuons.at(imu)->pt);
      if(matchedMuons.at(imu)->pt<30) continue;
      nMatchedMuPtCut+=1;
      MatchedMu_Eta->Fill(matchedMuons.at(imu)->eta);
      if(matchedMuons.at(imu)->eta>2.4) continue;
      nMatchedMuEtaCut+=1;
      MatchedMu_Chi2->Fill(matchedMuons.at(imu)->chi2);
      if(matchedMuons.at(imu)->chi2 > 10) continue;
      nMatchedMuChi2Cut+=1;
      MatchedMu_dz->Fill(matchedMuons.at(imu)->dz);
      if(matchedMuons.at(imu)->dz>0.5) continue;
      nMatchedMudZCut+=1;
      MatchedMu_dxy->Fill(matchedMuons.at(imu)->dxy);
      if(matchedMuons.at(imu)->dxy>0.2) continue;
      nMatchedMudXYCut+=1;
      MatchedMu_nValMuHits->Fill(matchedMuons.at(imu)->nValMuHits);
      if(matchedMuons.at(imu)->nValMuHits < 1 ) continue;
      nMatchedMuNValMuHitsCut+=1;
      MatchedMu_nMatchedStations->Fill(matchedMuons.at(imu)->nMatchedStations);
      if(matchedMuons.at(imu)->nMatchedStations<2) continue;
      nMatchedMuNMatchedStationsCut+=1;
      MatchedMu_nValPixelHits->Fill(matchedMuons.at(imu)->nValPixelHits);
      if(matchedMuons.at(imu)->nValPixelHits < 1) continue;
      nMatchedMuNValPixHitsCut+=1;
      MatchedMu_nTrackerLayers->Fill(matchedMuons.at(imu)->nTrackerLayers);
      if(matchedMuons.at(imu)->nTrackerLayers<6) continue;
      nMatchedMuNTrackLayersCut+=1;
      MatchedMu_relIso->Fill(matchedMuons.at(imu)->relIso);
      if(matchedMuons.at(imu)->relIso>0.20) continue;
      nMatchedMuRelIsoCut+=1;
    }

    /*NOW CUT ON ONLY EVENTS WITH TWO SAME SIGN LEPTONS FROM THE HARD SCATTERING*/
    bool samesign=false;
    //run through gen particle collection:
    for(unsigned int igen=0; igen<tr->genParticles.size(); igen++){
      //only run over electrons and muons from hard scattering
      if(!( ( fabs(tr->genParticles.at(igen)->id)==13 || fabs(tr->genParticles.at(igen)->id)==11) && (tr->genParticles.at(igen)->status==23 || tr->genParticles.at(igen)->status==1)) ) continue;
      //make sure genlepton is within detector acceptance
      if(! ( tr->genParticles.at(igen)->eta < 2.4)) continue;
      //check against the rest of the gen particles
      for(unsigned int jgen=igen+1; jgen<tr->genParticles.size();jgen++){
	if(!( ( fabs(tr->genParticles.at(jgen)->id)==13 || fabs(tr->genParticles.at(jgen)->id)==11) && (tr->genParticles.at(jgen)->status==23 || tr->genParticles.at(jgen)->status==1)) ) continue;
	//make sure genlepton is within detector acceptance
	if(! ( tr->genParticles.at(jgen)->eta < 2.4)) continue;
	//if same id then same-sign since not using fabs and these are already only looking at leptons from hard scattering
	if( tr->genParticles.at(igen)->id==tr->genParticles.at(jgen)->id) samesign=true;
	//or if both are greater than zero same sign since looking only at electrons and muons from hard scattering
	else if( (tr->genParticles.at(igen)->id >0) && (tr->genParticles.at(jgen)->id >0 ) ) samesign=true;
	//or if both are less than zero same sign since looking only at electrons and muons from hard scattering
	else if( (tr->genParticles.at(igen)->id <0) && (tr->genParticles.at(jgen)->id <0 ) ) samesign=true;
	//check to see how many events per channel
	if(fabs(tr->genParticles.at(igen)->id)==13 && fabs(tr->genParticles.at(jgen)->id)==13) nMuMu+=1;
	if(fabs(tr->genParticles.at(igen)->id)==11 && fabs(tr->genParticles.at(jgen)->id)==11) nElEl+=1;
	else nElMu+=1;
      }
    }
    if(!samesign) continue;
    int nMatchedMuMu=0;
    //now do cut flow for muons in same sign dilepton states
    for(unsigned int imu=0; imu< matchedMuons.size(); imu++){
      //skip if not at least a loose muon
      if(! matchedMuons.at(imu)->cutBasedLoose() ) continue;
      nAllMatchedMuSS+=1;
      MatchedMuSS_Global->Fill(matchedMuons.at(imu)->Global);
      if(! matchedMuons.at(imu)->Global) continue;
      nMatchedMuSSGlobalCut+=1;
      MatchedMuSS_PF->Fill(matchedMuons.at(imu)->PFMuon);
      if(! matchedMuons.at(imu)->PFMuon) continue;
      nMatchedMuSSPFCut+=1;
      MatchedMuSS_Pt->Fill(matchedMuons.at(imu)->pt);
      if(matchedMuons.at(imu)->pt<30) continue;
      nMatchedMuSSPtCut+=1;
      MatchedMuSS_Eta->Fill(matchedMuons.at(imu)->eta);
      if(matchedMuons.at(imu)->eta>2.4) continue;
      nMatchedMuSSEtaCut+=1;
      MatchedMuSS_Chi2->Fill(matchedMuons.at(imu)->chi2);
      if(matchedMuons.at(imu)->chi2 > 10) continue;
      nMatchedMuSSChi2Cut+=1;
      MatchedMuSS_dz->Fill(matchedMuons.at(imu)->dz);
      if(matchedMuons.at(imu)->dz>0.5) continue;
      nMatchedMuSSdZCut+=1;
      MatchedMuSS_dxy->Fill(matchedMuons.at(imu)->dxy);
      if(matchedMuons.at(imu)->dxy>0.2) continue;
      nMatchedMuSSdXYCut+=1;
      MatchedMuSS_nValMuHits->Fill(matchedMuons.at(imu)->nValMuHits);
      if(matchedMuons.at(imu)->nValMuHits < 1 ) continue;
      nMatchedMuSSNValMuHitsCut+=1;
      MatchedMuSS_nMatchedStations->Fill(matchedMuons.at(imu)->nMatchedStations);
      if(matchedMuons.at(imu)->nMatchedStations<2) continue;
      nMatchedMuSSNMatchedStationsCut+=1;
      MatchedMuSS_nValPixelHits->Fill(matchedMuons.at(imu)->nValPixelHits);
      if(matchedMuons.at(imu)->nValPixelHits < 1) continue;
      nMatchedMuSSNValPixHitsCut+=1;
      MatchedMuSS_nTrackerLayers->Fill(matchedMuons.at(imu)->nTrackerLayers);
      if(matchedMuons.at(imu)->nTrackerLayers<6) continue;
      nMatchedMuSSNTrackLayersCut+=1;
      MatchedMuSS_relIso->Fill(matchedMuons.at(imu)->relIso);
      if(matchedMuons.at(imu)->relIso>0.20) continue;
      nMatchedMuSSRelIsoCut+=1;
      nMatchedMuMu+=1;
    }

    if(nMatchedMuMu==2) nRecoMuMu+=1;


  }
  

  TH1F* MatchedMuCutHist = new TH1F("MatchedMuCutHist","Cut Flow For Muon Selection",13,0,13);
  MatchedMuCutHist->SetBinContent(1,1);                                                 MatchedMuCutHist->GetXaxis()->SetBinLabel(1,"All Loose Muons");
  MatchedMuCutHist->SetBinContent(2,nMatchedMuGlobalCut/nAllMatchedMu);                  MatchedMuCutHist->GetXaxis()->SetBinLabel(2,"is GlobalMuon");
  MatchedMuCutHist->SetBinContent(3,nMatchedMuPFCut/nMatchedMuGlobalCut);               MatchedMuCutHist->GetXaxis()->SetBinLabel(3,"is PF Muon");
  MatchedMuCutHist->SetBinContent(4,nMatchedMuPtCut/nMatchedMuPFCut);                   MatchedMuCutHist->GetXaxis()->SetBinLabel(4,"p_{T} >30");
  MatchedMuCutHist->SetBinContent(5,nMatchedMuEtaCut/nMatchedMuPtCut);                  MatchedMuCutHist->GetXaxis()->SetBinLabel(5,"#eta <2.4");
  MatchedMuCutHist->SetBinContent(6,nMatchedMuChi2Cut/nMatchedMuEtaCut);                MatchedMuCutHist->GetXaxis()->SetBinLabel(6,"#chi^{2} <10");
  MatchedMuCutHist->SetBinContent(7,nMatchedMudZCut/nMatchedMuChi2Cut);                 MatchedMuCutHist->GetXaxis()->SetBinLabel(7,"dZ<0.5");
  MatchedMuCutHist->SetBinContent(8,nMatchedMudXYCut/nMatchedMudZCut);                  MatchedMuCutHist->GetXaxis()->SetBinLabel(8,"dXY<0.2");
  MatchedMuCutHist->SetBinContent(9,nMatchedMuNValMuHitsCut/nMatchedMudXYCut);          MatchedMuCutHist->GetXaxis()->SetBinLabel(9,"N_{ValidMuHits}>=1");
  MatchedMuCutHist->SetBinContent(10,nMatchedMuNMatchedStationsCut/nMatchedMuNValMuHitsCut);  MatchedMuCutHist->GetXaxis()->SetBinLabel(10,"N_{MatchStations}>=2");
  MatchedMuCutHist->SetBinContent(11,nMatchedMuNValPixHitsCut/nMatchedMuNMatchedStationsCut); MatchedMuCutHist->GetXaxis()->SetBinLabel(11,"N_{ValidPixHits}>=1");
  MatchedMuCutHist->SetBinContent(12,nMatchedMuNTrackLayersCut/nMatchedMuNValPixHitsCut);  MatchedMuCutHist->GetXaxis()->SetBinLabel(12,"N_{TrackerLayer}>5");
  MatchedMuCutHist->SetBinContent(13,nMatchedMuRelIsoCut/nMatchedMuNTrackLayersCut);       MatchedMuCutHist->GetXaxis()->SetBinLabel(13,"RelIso <0.2");

  TH1F* MatchedMuSSCutHist = new TH1F("MatchedMuSSCutHist","Cut Flow For Muon Selection",13,0,13);
  MatchedMuSSCutHist->SetBinContent(1,1);                                                     MatchedMuSSCutHist->GetXaxis()->SetBinLabel(1,"All Loose Muons");
  MatchedMuSSCutHist->SetBinContent(2,nMatchedMuSSGlobalCut/nAllMatchedMuSS);                    MatchedMuSSCutHist->GetXaxis()->SetBinLabel(2,"is GlobalMuon");
  MatchedMuSSCutHist->SetBinContent(3,nMatchedMuSSPFCut/nMatchedMuSSGlobalCut);                 MatchedMuSSCutHist->GetXaxis()->SetBinLabel(3,"is PF Muon");
  MatchedMuSSCutHist->SetBinContent(4,nMatchedMuSSPtCut/nMatchedMuSSPFCut);                   MatchedMuSSCutHist->GetXaxis()->SetBinLabel(4,"p_{T} >30");
  MatchedMuSSCutHist->SetBinContent(5,nMatchedMuSSEtaCut/nMatchedMuSSPtCut);                  MatchedMuSSCutHist->GetXaxis()->SetBinLabel(5,"#eta <2.4");
  MatchedMuSSCutHist->SetBinContent(6,nMatchedMuSSChi2Cut/nMatchedMuSSEtaCut);                MatchedMuSSCutHist->GetXaxis()->SetBinLabel(6,"#chi^{2} <10");
  MatchedMuSSCutHist->SetBinContent(7,nMatchedMuSSdZCut/nMatchedMuSSChi2Cut);                 MatchedMuSSCutHist->GetXaxis()->SetBinLabel(7,"dZ<0.5");
  MatchedMuSSCutHist->SetBinContent(8,nMatchedMuSSdXYCut/nMatchedMuSSdZCut);                  MatchedMuSSCutHist->GetXaxis()->SetBinLabel(8,"dXY<0.2");
  MatchedMuSSCutHist->SetBinContent(9,nMatchedMuSSNValMuHitsCut/nMatchedMuSSdXYCut);          MatchedMuSSCutHist->GetXaxis()->SetBinLabel(9,"N_{ValidMuHits}>=1");
  MatchedMuSSCutHist->SetBinContent(10,nMatchedMuSSNMatchedStationsCut/nMatchedMuSSNValMuHitsCut);  MatchedMuSSCutHist->GetXaxis()->SetBinLabel(10,"N_{MatchStations}>=2");
  MatchedMuSSCutHist->SetBinContent(11,nMatchedMuSSNValPixHitsCut/nMatchedMuSSNMatchedStationsCut); MatchedMuSSCutHist->GetXaxis()->SetBinLabel(11,"N_{ValidPixHits}>=1");
  MatchedMuSSCutHist->SetBinContent(12,nMatchedMuSSNTrackLayersCut/nMatchedMuSSNValPixHitsCut);  MatchedMuSSCutHist->GetXaxis()->SetBinLabel(12,"N_{TrackerLayer}>5");
  MatchedMuSSCutHist->SetBinContent(13,nMatchedMuSSRelIsoCut/nMatchedMuSSNTrackLayersCut);       MatchedMuSSCutHist->GetXaxis()->SetBinLabel(13,"RelIso <0.2");


  std::cout<<"Total efficiency for loose muons becoming tight: "<<nMatchedMuRelIsoCut/nAllMatchedMu<<std::endl;
  std::cout<<"Total efficiency for loose muons becoming tight in SS events: "<<nMatchedMuSSRelIsoCut/nAllMatchedMuSS<<std::endl;
  outFile->Write();

  std::cout<<"Number of MuMu Gen events is: "<<nMuMu<<std::endl;
  std::cout<<"Number of MuMu RECO events is: "<<nRecoMuMu<<std::endl<<std::endl;
  std::cout<<"Number of ElEl Gen events is: "<<nElEl<<std::endl;
  std::cout<<"Number of ElMu Gen events is: "<<nElMu<<std::endl;
}

void doBarrelElectronCutFlow(TFile* outFile, TTree* t, TreeReader* tr){

  //for safety always change to top directory
  outFile->cd();
  TDirectory *elDir =  outFile->mkdir("ElectronBarrelCutFlow");
  elDir->cd();
  //histograms for Electron variables
  TH1F* MatchedElBarrel_Pt= new TH1F("MatchedElBarrel_pt","p_{T} of loose OR tight electrons in same-sign events",100,0,500);
  TH1F* MatchedElBarrel_dEta= new TH1F("MatchedElBarrel_dEta","dEta of loose OR tight electrons in same-sign events",10,-0.01,0.01);
  TH1F* MatchedElBarrel_dPhi= new TH1F("MatchedElBarrel_dPhi","dPhi of loose OR tight electrons in same-sign events",10,-0.2,0.2);
  TH1F* MatchedElBarrel_dZ= new TH1F("MatchedElBarrel_dZ","dZ of loose OR tight electrons in same-sign events",50,0,.1);
  TH1F* MatchedElBarrel_d0= new TH1F("MatchedElBarrel_d0","d0 of loose OR tight electrons in same-sign events",50,0,.1);
  TH1F* MatchedElBarrel_hOverE= new TH1F("MatchedElBarrel_hOverE","HoverE of loose OR tight electrons in same-sign events",20,0,.15);
  TH1F* MatchedElBarrel_mHits= new TH1F("MatchedElBarrel_mHits","N_{MissingHits} of loose OR tight electrons in same-sign events",10,0,10);
  TH1F* MatchedElBarrel_ooEmooP= new TH1F("MatchedElBarrel_ooEmooP","1/E - 1/P of loose OR tight electrons in same-sign events",20,0,0.1);
  TH1F* MatchedElBarrel_relIsoEA= new TH1F("MatchedElBarrel_relIsoEA","RelIso of loose OR tight electrons in same-sign events",20,0,1);
  TH1F* MatchedElBarrel_sigmaIetaIeta= new TH1F("MatchedElBarrel_sigmaIetaIeta","sigmaIetaIeta of loose OR tight electrons in same-sign events",25,0,.02);
  TH1F* MatchedElBarrel_chargeConsistency= new TH1F("MatchedElBarrel_chargeConsistency","charge consistency of loose OR tight electrons in same-sign events",3,-1.5,1.5);

  //histograms for Electron variables
  TH1F* MatchedElBarrelSS_Pt= new TH1F("MatchedElBarrelSS_pt","p_{T} of loose OR tight electrons in same-sign events",100,0,500);
  TH1F* MatchedElBarrelSS_dEta= new TH1F("MatchedElBarrelSS_dEta","dEta of loose OR tight electrons in same-sign events",10,-0.01,0.01);
  TH1F* MatchedElBarrelSS_dPhi= new TH1F("MatchedElBarrelSS_dPhi","dPhi of loose OR tight electrons in same-sign events",10,-0.2,0.2);
  TH1F* MatchedElBarrelSS_dZ= new TH1F("MatchedElBarrelSS_dZ","dZ of loose OR tight electrons in same-sign events",50,0,.1);
  TH1F* MatchedElBarrelSS_d0= new TH1F("MatchedElBarrelSS_d0","d0 of loose OR tight electrons in same-sign events",50,0,.1);
  TH1F* MatchedElBarrelSS_hOverE= new TH1F("MatchedElBarrelSS_hOverE","HoverE of loose OR tight electrons in same-sign events",20,0,.15);
  TH1F* MatchedElBarrelSS_mHits= new TH1F("MatchedElBarrelSS_mHits","N_{MissingHits} of loose OR tight electrons in same-sign events",10,0,10);
  TH1F* MatchedElBarrelSS_ooEmooP= new TH1F("MatchedElBarrelSS_ooEmooP","1/E - 1/P of loose OR tight electrons in same-sign events",20,0,0.1);
  TH1F* MatchedElBarrelSS_relIsoEA= new TH1F("MatchedElBarrelSS_relIsoEA","RelIso of loose OR tight electrons in same-sign events",20,0,1);
  TH1F* MatchedElBarrelSS_sigmaIetaIeta= new TH1F("MatchedElBarrelSS_sigmaIetaIeta","sigmaIetaIeta of loose OR tight electrons in same-sign events",25,0,.02);
  TH1F* MatchedElBarrelSS_chargeConsistency= new TH1F("MatchedElBarrelSS_chargeConsistency","charge consistency of loose OR tight electrons in same-sign events",3,-1.5,1.5);

  int nEntries = t->GetEntries();

  float nAllMatchedElBarrel=0;
  float nMatchedElBarrelPtCut=0;
  float nMatchedElBarreldEtaCut=0;
  float nMatchedElBarreldPhiCut=0;
  float nMatchedElBarrelsigmaIetaIetaCut=0;
  float nMatchedElBarrelhOverECut=0;
  float nMatchedElBarrelooEmooPCut=0;
  float nMatchedElBarreld0Cut=0;
  float nMatchedElBarreldZCut=0;
  float nMatchedElBarrelRelIsoCut=0;
  float nMatchedElBarrelmHitsCut=0;
  float nMatchedElBarrelchargeConsistencyCut=0;

  float nAllMatchedElBarrelSS=0;
  float nMatchedElBarrelSSPtCut=0;
  float nMatchedElBarrelSSdEtaCut=0;
  float nMatchedElBarrelSSdPhiCut=0;
  float nMatchedElBarrelSSsigmaIetaIetaCut=0;
  float nMatchedElBarrelSShOverECut=0;
  float nMatchedElBarrelSSooEmooPCut=0;
  float nMatchedElBarrelSSd0Cut=0;
  float nMatchedElBarrelSSdZCut=0;
  float nMatchedElBarrelSSRelIsoCut=0;
  float nMatchedElBarrelSSmHitsCut=0;
  float nMatchedElBarrelSSchargeConsistencyCut=0;

  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    tr->GetEntry(ient);
    

    /* FIRST DO CUT FLOW FOR ALL MUONS MATCHED TO A MUON FROM THE HARD SCATTERING*/

    //match muons to status three leptons
    std::vector<TElectron*> matchedElectrons;
    for(unsigned int iel=0; iel< tr->allElectrons.size(); iel++){
      float dR=100;


      //run through gen particle collection:
      for(unsigned int igen=0; igen<tr->genParticles.size(); igen++){
	//only run over muons from hard scattering
	if(!( ( fabs(tr->genParticles.at(igen)->id)==11) && (tr->genParticles.at(igen)->status==23 || tr->genParticles.at(igen)->status==1)) ) continue;
	float drtemp = pow( pow( tr->allElectrons.at(iel)->eta - tr->genParticles.at(igen)->eta, 2 ) + pow( tr->allElectrons.at(iel)->phi - tr->genParticles.at(igen)->phi, 2), 0.5);
	if(drtemp < dR){
	  dR = drtemp;
	}
      }

      //now we have a min deltaR between our muon and all muons from hard scattering, if it is less than 0.3 let's consider it matched
      if(dR <0.15){
	matchedElectrons.push_back(tr->allElectrons.at(iel));
      }
    }
    

    //now that we have our vector of matched mouns we can do a cut flow for them

    for(unsigned int iel=0; iel< matchedElectrons.size(); iel++){
      //veto not in Barrel
      if(matchedElectrons.at(iel)->eta > 1.479) continue;
      //skip if not at least a loose electron
      if(! matchedElectrons.at(iel)->cutBasedLoose() ) continue;
      nAllMatchedElBarrel+=1;
      MatchedElBarrel_Pt->Fill(matchedElectrons.at(iel)->pt);
      if(matchedElectrons.at(iel)->pt<30) continue;
      nMatchedElBarrelPtCut+=1;
      MatchedElBarrel_dEta->Fill(matchedElectrons.at(iel)->dEta);
      if(fabs(matchedElectrons.at(iel)->dEta)>=0.006574) continue;
      nMatchedElBarreldEtaCut+=1;
      MatchedElBarrel_dPhi->Fill(matchedElectrons.at(iel)->dPhi);
      if(fabs(matchedElectrons.at(iel)->dPhi) >= 0.022868) continue;
      nMatchedElBarreldPhiCut+=1;
      MatchedElBarrel_sigmaIetaIeta->Fill(matchedElectrons.at(iel)->sigmaIetaIeta);
      if(matchedElectrons.at(iel)->sigmaIetaIeta>= 0.010181) continue;
      nMatchedElBarrelsigmaIetaIetaCut+=1;
      MatchedElBarrel_hOverE->Fill(matchedElectrons.at(iel)->hOverE);
      if(matchedElectrons.at(iel)->hOverE >= 0.037553) continue;
      nMatchedElBarrelhOverECut+=1;
      MatchedElBarrel_d0->Fill(matchedElectrons.at(iel)->d0);
      if(fabs(matchedElectrons.at(iel)->d0)>= 0.009924 ) continue;
      nMatchedElBarreld0Cut+=1;
      MatchedElBarrel_dZ->Fill(matchedElectrons.at(iel)->dZ);
      if(fabs(matchedElectrons.at(iel)->dZ) >= 0.015310) continue;
      nMatchedElBarreldZCut+=1;
      MatchedElBarrel_ooEmooP->Fill(matchedElectrons.at(iel)->ooEmooP);
      if(matchedElectrons.at(iel)->ooEmooP >=0.131191) continue;
      nMatchedElBarrelooEmooPCut+=1;
      MatchedElBarrel_mHits->Fill(matchedElectrons.at(iel)->mHits);
      if(matchedElectrons.at(iel)->mHits > 1) continue;
      nMatchedElBarrelmHitsCut+=1;
      MatchedElBarrel_relIsoEA->Fill(matchedElectrons.at(iel)->relIsoEA);
      if(matchedElectrons.at(iel)->relIsoEA>0.1649) continue;
      nMatchedElBarrelRelIsoCut+=1;
      MatchedElBarrel_chargeConsistency->Fill(matchedElectrons.at(iel)->chargeConsistency);
      if(matchedElectrons.at(iel)->chargeConsistency<1) continue;
      nMatchedElBarrelchargeConsistencyCut+=1;
    }

    /*NOW CUT ON ONLY EVENTS WITH TWO SAME SIGN LEPTONS FROM THE HARD SCATTERING*/
    bool samesign=false;
    //run through gen particle collection:
    for(unsigned int igen=0; igen<tr->genParticles.size(); igen++){
      //only run over electrons and muons from hard scattering
      if(!( ( fabs(tr->genParticles.at(igen)->id)==13 || fabs(tr->genParticles.at(igen)->id)==11) && (tr->genParticles.at(igen)->status==23 || tr->genParticles.at(igen)->status==1)) ) continue;
      //check against the rest of the gen particles
      for(unsigned int jgen=igen+1; jgen<tr->genParticles.size();jgen++){
	if(!( ( fabs(tr->genParticles.at(jgen)->id)==13 || fabs(tr->genParticles.at(jgen)->id)==11) && (tr->genParticles.at(jgen)->status==23 || tr->genParticles.at(jgen)->status==1)) ) continue;
	//if same id then same-sign since not using fabs and these are already only looking at leptons from hard scattering
	if( tr->genParticles.at(igen)->id==tr->genParticles.at(jgen)->id) samesign=true;
	//or if both are greater than zero same sign since looking only at electrons and muons from hard scattering
	else if( (tr->genParticles.at(igen)->id >0) && (tr->genParticles.at(jgen)->id >0 ) ) samesign=true;
	//or if both are less than zero same sign since looking only at electrons and muons from hard scattering
	else if( (tr->genParticles.at(igen)->id <0) && (tr->genParticles.at(jgen)->id <0 ) ) samesign=true;
      }
    }
    if(!samesign) continue;

    for(unsigned int iel=0; iel< matchedElectrons.size(); iel++){
      //veto if not in barrel
      if(matchedElectrons.at(iel)->eta > 1.479) continue;
      //skip if not at least a loose electron
      if(! matchedElectrons.at(iel)->cutBasedLoose() ) continue;
      nAllMatchedElBarrelSS+=1;
      MatchedElBarrelSS_Pt->Fill(matchedElectrons.at(iel)->pt);
      if(matchedElectrons.at(iel)->pt<30) continue;
      nMatchedElBarrelSSPtCut+=1;
      MatchedElBarrelSS_dEta->Fill(matchedElectrons.at(iel)->dEta);
      if(fabs(matchedElectrons.at(iel)->dEta)>=0.006574) continue;
      nMatchedElBarrelSSdEtaCut+=1;
      MatchedElBarrelSS_dPhi->Fill(matchedElectrons.at(iel)->dPhi);
      if(fabs(matchedElectrons.at(iel)->dPhi) >= 0.022868) continue;
      nMatchedElBarrelSSdPhiCut+=1;
      MatchedElBarrelSS_sigmaIetaIeta->Fill(matchedElectrons.at(iel)->sigmaIetaIeta);
      if(matchedElectrons.at(iel)->sigmaIetaIeta>= 0.010181) continue;
      nMatchedElBarrelSSsigmaIetaIetaCut+=1;
      MatchedElBarrelSS_hOverE->Fill(matchedElectrons.at(iel)->hOverE);
      if(matchedElectrons.at(iel)->hOverE >= 0.037553) continue;
      nMatchedElBarrelSShOverECut+=1;
      MatchedElBarrelSS_d0->Fill(matchedElectrons.at(iel)->d0);
      if(fabs(matchedElectrons.at(iel)->d0)>= 0.009924 ) continue;
      nMatchedElBarrelSSd0Cut+=1;
      MatchedElBarrelSS_dZ->Fill(matchedElectrons.at(iel)->dZ);
      if(fabs(matchedElectrons.at(iel)->dZ) >= 0.015310) continue;
      nMatchedElBarrelSSdZCut+=1;
      MatchedElBarrelSS_ooEmooP->Fill(matchedElectrons.at(iel)->ooEmooP);
      if(matchedElectrons.at(iel)->ooEmooP >=0.131191) continue;
      nMatchedElBarrelSSooEmooPCut+=1;
      MatchedElBarrelSS_mHits->Fill(matchedElectrons.at(iel)->mHits);
      if(matchedElectrons.at(iel)->mHits > 1) continue;
      nMatchedElBarrelSSmHitsCut+=1;
      MatchedElBarrelSS_relIsoEA->Fill(matchedElectrons.at(iel)->relIsoEA);
      if(matchedElectrons.at(iel)->relIsoEA>0.1649) continue;
      nMatchedElBarrelSSRelIsoCut+=1;
      MatchedElBarrelSS_chargeConsistency->Fill(matchedElectrons.at(iel)->chargeConsistency);
      if(matchedElectrons.at(iel)->chargeConsistency<1) continue;
      nMatchedElBarrelSSchargeConsistencyCut+=1;
      
    }
    
  }  

  TH1F* MatchedElBarrelCutHist = new TH1F("MatchedElBarrelCutHist","Cut Flow For Electron Selection",12,0,12);
  MatchedElBarrelCutHist->SetBinContent(1,1);                                                               MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(1,"All Loose Electrons");
  MatchedElBarrelCutHist->SetBinContent(2,nMatchedElBarrelPtCut/nAllMatchedElBarrel);                       MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(2,"p_{T} >30");
  MatchedElBarrelCutHist->SetBinContent(3,nMatchedElBarreldEtaCut/nMatchedElBarrelPtCut);                   MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(3,"#Delta_{#eta}<0.006574");
  MatchedElBarrelCutHist->SetBinContent(4,nMatchedElBarreldPhiCut/nMatchedElBarreldEtaCut);                 MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(4,"#Delta_{#phi}<0.022868");
  MatchedElBarrelCutHist->SetBinContent(5,nMatchedElBarrelsigmaIetaIetaCut/nMatchedElBarreldPhiCut);        MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(5,"#sigma_{I#etaI#eta}<0.010181");
  MatchedElBarrelCutHist->SetBinContent(6,nMatchedElBarrelhOverECut/nMatchedElBarrelsigmaIetaIetaCut);      MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(6,"H/E <0.037553");
  MatchedElBarrelCutHist->SetBinContent(7,nMatchedElBarreld0Cut/nMatchedElBarrelhOverECut);                 MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(7,"d0<0.009924");
  MatchedElBarrelCutHist->SetBinContent(8,nMatchedElBarreldZCut/nMatchedElBarreld0Cut);                     MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(8,"dZ<0.015310");
  MatchedElBarrelCutHist->SetBinContent(9,nMatchedElBarrelooEmooPCut/nMatchedElBarreldZCut);                MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(9,"1/E - 1/P <0.131191");
  MatchedElBarrelCutHist->SetBinContent(10,nMatchedElBarrelmHitsCut/nMatchedElBarrelooEmooPCut);            MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(10,"Missing Hits <1");
  MatchedElBarrelCutHist->SetBinContent(11,nMatchedElBarrelRelIsoCut/nMatchedElBarrelmHitsCut);             MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(11,"RelIso <0.1649");
  MatchedElBarrelCutHist->SetBinContent(12,nMatchedElBarrelchargeConsistencyCut/nMatchedElBarrelRelIsoCut); MatchedElBarrelCutHist->GetXaxis()->SetBinLabel(12,"chargeConsistent");
 
  TH1F* MatchedElBarrelSSCutHist = new TH1F("MatchedElBarrelSSCutHist","Cut Flow For Electron Selection",12,0,12);
  MatchedElBarrelSSCutHist->SetBinContent(1,1);                                                               MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(1,"All Loose Electrons");
  MatchedElBarrelSSCutHist->SetBinContent(2,nMatchedElBarrelSSPtCut/nAllMatchedElBarrelSS);                       MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(2,"p_{T} >30");
  MatchedElBarrelSSCutHist->SetBinContent(3,nMatchedElBarrelSSdEtaCut/nMatchedElBarrelSSPtCut);                   MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(3,"#Delta_{#eta}<0.006574");
  MatchedElBarrelSSCutHist->SetBinContent(4,nMatchedElBarrelSSdPhiCut/nMatchedElBarrelSSdEtaCut);                 MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(4,"#Delta_{#phi}<0.022868");
  MatchedElBarrelSSCutHist->SetBinContent(5,nMatchedElBarrelSSsigmaIetaIetaCut/nMatchedElBarrelSSdPhiCut);        MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(5,"#sigma_{I#etaI#eta}<0.010181");
  MatchedElBarrelSSCutHist->SetBinContent(6,nMatchedElBarrelSShOverECut/nMatchedElBarrelSSsigmaIetaIetaCut);      MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(6,"H/E <0.037553");
  MatchedElBarrelSSCutHist->SetBinContent(7,nMatchedElBarrelSSd0Cut/nMatchedElBarrelSShOverECut);                 MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(7,"d0<0.009924");
  MatchedElBarrelSSCutHist->SetBinContent(8,nMatchedElBarrelSSdZCut/nMatchedElBarrelSSd0Cut);                     MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(8,"dZ<0.015310");
  MatchedElBarrelSSCutHist->SetBinContent(9,nMatchedElBarrelSSooEmooPCut/nMatchedElBarrelSSdZCut);                MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(9,"1/E - 1/P <0.131191");
  MatchedElBarrelSSCutHist->SetBinContent(10,nMatchedElBarrelSSmHitsCut/nMatchedElBarrelSSooEmooPCut);            MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(10,"Missing Hits <1");
  MatchedElBarrelSSCutHist->SetBinContent(11,nMatchedElBarrelSSRelIsoCut/nMatchedElBarrelSSmHitsCut);             MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(11,"RelIso <0.1649");
  MatchedElBarrelSSCutHist->SetBinContent(12,nMatchedElBarrelSSchargeConsistencyCut/nMatchedElBarrelSSRelIsoCut); MatchedElBarrelSSCutHist->GetXaxis()->SetBinLabel(12,"chargeConsistent");
 
  
  std::cout<<"Total efficiency for loose electrons becoming tight: "<<nMatchedElBarrelRelIsoCut/nAllMatchedElBarrel<<std::endl;
  std::cout<<"Total efficiency for loose electrons becoming tight in SS events: "<<nMatchedElBarrelSSRelIsoCut/nAllMatchedElBarrelSS<<std::endl;
  outFile->Write();
  
  
}
