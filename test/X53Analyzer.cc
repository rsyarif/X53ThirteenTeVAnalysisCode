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

int main(int argc, char* argv[]){
  //make TreeReader
  TString filename(argv[1]);
  TreeReader* tr= new TreeReader(filename);
  TTree* t=tr->tree;  

  TFile* fsig = new TFile("LeptonDists_1000_NewIso_rh_pair.root","RECREATE");

  TH1F* h_MuCutFlow = new TH1F("h_MuCutFlow","Cut Flow For Muons",13,0,13);
  TH1F* h_DilepMass = new TH1F("h_DilepMass","Generator Level Dilepton Mass", 25, 0, 1000);
  TH1F* h_GenHT = new TH1F("h_GenHT","Generator HT", 75,0,3000);

  /* doMuonCutFlow(fsig,t,tr);
  doBarrelElectronCutFlow(fsig,t,tr);
  DrawGenJetHists(fsig,t,tr);
  DrawAK4JetHists(fsig,t,tr);*/
  //MakeJetResponseHist(fsig,t,tr);

  int nEntries = t->GetEntries();

  int nMuMu=0;
  int nElMu=0;
  int nElEl=0;

  for(int ient=0; ient<nEntries; ient++){

    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    tr->GetEntry(ient);


    bool GenSamesign=false;
    std::vector<TGenParticle*> vSSGenLep;
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
	if( tr->genParticles.at(igen)->id==tr->genParticles.at(jgen)->id) GenSamesign=true;
	//or if both are greater than zero same sign since looking only at electrons and muons from hard scattering
	else if( (tr->genParticles.at(igen)->id >0) && (tr->genParticles.at(jgen)->id >0 ) ) GenSamesign=true;
	//or if both are less than zero same sign since looking only at electrons and muons from hard scattering
	else if( (tr->genParticles.at(igen)->id <0) && (tr->genParticles.at(jgen)->id <0 ) ) GenSamesign=true;
	if(GenSamesign){
	  vSSGenLep.push_back(tr->genParticles.at(igen));
	  vSSGenLep.push_back(tr->genParticles.at(jgen));
	}

      }
    }

    if(GenSamesign){
      TLorentzVector v1 = vSSGenLep.at(0)->lv;
      TLorentzVector v2 = vSSGenLep.at(1)->lv;
      float dilepmass = (v1+v2).M();
      h_DilepMass->Fill(dilepmass);
      
      float HT=0;
      for(unsigned int uijet=0; uijet<tr->genJets.size();uijet++){
	HT+=tr->genJets.at(uijet)->pt;
      }
      h_GenHT->Fill(HT);
    }


    //Muon CutFlow                                                                                                                                                                                               
    for(unsigned int uimu=0; uimu<tr->allMuons.size();uimu++){
      TMuon* imu = tr->allMuons.at(uimu);

      //run through gen particle collection:                                                                                                                                                                      
      float dR=999;
      for(unsigned int igen=0; igen<tr->genParticles.size(); igen++){
        //only run over muons from hard scattering                                                                                                                                                               
        if(!( ( fabs(tr->genParticles.at(igen)->id)==13) && (tr->genParticles.at(igen)->status==23 || tr->genParticles.at(igen)->status==1)) ) continue;
        float drtemp = pow( pow( imu->eta - tr->genParticles.at(igen)->eta, 2 ) + pow( imu->phi - tr->genParticles.at(igen)->phi, 2), 0.5);
        if(drtemp < dR){
          dR = drtemp;
        }
      }

      //now check to make sure the muon is matched by requiring deltaR be les than 0.15                                                                                                                           
      if(dR >= 0.15) continue;

      if(imu->PFMuon) h_MuCutFlow->Fill(0.5,1);
      else continue;
      if(imu->Global || imu->Tracker) h_MuCutFlow->Fill(1.5,1);
      else continue;
      if(imu->Global) h_MuCutFlow->Fill(2.5,1);
      else continue;
      if(imu->pt>30) h_MuCutFlow->Fill(3.5,1);
      else continue;
      if(imu->eta < 2.4) h_MuCutFlow->Fill(4.5,1);
      else continue;
      if(imu->chi2<10) h_MuCutFlow->Fill(5.5,1);
      else continue;
      if(imu->dz < 0.5) h_MuCutFlow->Fill(6.5,1);
      else continue;
      if(imu->dxy < 0.2) h_MuCutFlow->Fill(7.5,1);
      else continue;
      if(imu->nValMuHits>=1) h_MuCutFlow->Fill(8.5,1);
      else continue;
      if(imu->nMatchedStations >=2) h_MuCutFlow->Fill(9.5,1);
      else continue;
      if(imu->nValPixelHits >=1) h_MuCutFlow->Fill(10.5,1);
      else continue;
      if(imu->nTrackerLayers > 5) h_MuCutFlow->Fill(11.5,1);
      else continue;
      if(imu->relIso < 0.2) h_MuCutFlow->Fill(12.5,1);
    }


    //make vector of TLeptons
    std::vector<TLepton*> goodLeptons;

    //fill with good muons
    for(unsigned int uimu=0; uimu<tr->goodMuons.size(); uimu++){
      TMuon* imu = tr->goodMuons.at(uimu);
      TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);
      iLep->isMu = true;
      iLep->isEl = false;
      goodLeptons.push_back(iLep);
      //delete iLep;
    }

    //fill with good electrons
    for(unsigned int uiel=0; uiel<tr->goodElectrons.size(); uiel++){
      TElectron* iel = tr->goodElectrons.at(uiel);
      TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge);
      iLep->isMu = false;
      iLep->isEl = true;
      goodLeptons.push_back(iLep);
      //delete iLep;
    }

    //now that we have good leptons check for two with same-sign charge
    bool samesign =false;
    std::vector<TLepton*> vSSLep;
    for(unsigned int uilep=0; uilep<goodLeptons.size(); uilep++){
      for(unsigned int ujlep=uilep+1; ujlep<goodLeptons.size(); ujlep++){
	if(goodLeptons.at(uilep)->charge == goodLeptons.at(ujlep)->charge){
	  samesign=true;
	  vSSLep.push_back(goodLeptons.at(uilep));
	  vSSLep.push_back(goodLeptons.at(ujlep));
	}
      }
    }



    if(!samesign) continue;




    //ok at this point only have events with same-sign leptons, now let's do simple check to see how many of each channel we have:
    if(vSSLep.size()>2) std::cout<<"found two same-sign pairs"<<std::endl;

    if(vSSLep.at(0)->isMu && vSSLep.at(1)->isMu) nMuMu+=1;
    else if( ( vSSLep.at(0)->isEl && vSSLep.at(1)->isMu) || (vSSLep.at(0)->isMu && vSSLep.at(1)->isEl)) nElMu+=1;
    else nElEl+=1;

  }//end event loop

  //normalize cutflow to first bin                                                                                                                                                                                
  h_MuCutFlow->Scale( 1. / h_MuCutFlow->GetBinContent(1) );

  //set bin labels                                                                                                                                                                                                
  h_MuCutFlow->GetXaxis()->SetBinLabel(1,"All Loose Muons");
  h_MuCutFlow->GetXaxis()->SetBinLabel(2,"is GlobalMuon");
  h_MuCutFlow->GetXaxis()->SetBinLabel(3,"is PF Muon");
  h_MuCutFlow->GetXaxis()->SetBinLabel(4,"p_{T} >30");
  h_MuCutFlow->GetXaxis()->SetBinLabel(5,"#eta <2.4");
  h_MuCutFlow->GetXaxis()->SetBinLabel(6,"#chi^{2} <10");
  h_MuCutFlow->GetXaxis()->SetBinLabel(7,"dZ<0.5");
  h_MuCutFlow->GetXaxis()->SetBinLabel(8,"dXY<0.2");
  h_MuCutFlow->GetXaxis()->SetBinLabel(9,"N_{ValidMuHits}>=1");
  h_MuCutFlow->GetXaxis()->SetBinLabel(10,"N_{MatchStations}>=2");
  h_MuCutFlow->GetXaxis()->SetBinLabel(11,"N_{ValidPixHits}>=1");
  h_MuCutFlow->GetXaxis()->SetBinLabel(12,"N_{TrackerLayer}>5");
  h_MuCutFlow->GetXaxis()->SetBinLabel(13,"RelIso <0.2");


  fsig->Write();
  fsig->Close();

  std::cout<<"Number of MuMu: "<<nMuMu<<std::endl;
  std::cout<<"Number of ElMu: "<<nElMu<<std::endl;
  std::cout<<"Number of ElEl: "<<nElEl<<std::endl;

}
