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
TGenParticle* getMatchedGenParticle(TMuon* mu, std::vector<TGenParticle*> genParticles);
std::vector<TLepton*> makeOSLeptonsForDY(std::vector<TLepton*>);

int main(int argc, char* argv[]){

  //make output file
  TFile* fout = new TFile("IP_CrossCheck.root","RECREATE");


  TH1F* h_el_d0_np = new TH1F("h_el_d0_np","d0 of non-prompt ttbar electrons",1000,0,5);
  TH1F* h_el_d0_pttb = new TH1F("h_el_d0_pttb","d0 of prompt ttbar electrons",1000,0,5);
  TH1F* h_el_d0_lhsig = new TH1F("h_el_d0_lhsig","d0 of prompt LH signal electrons",1000,0,5);
  TH1F* h_el_d0_rhsig = new TH1F("h_el_d0_rhsig","d0 of prompt RH signal electrons",1000,0,5);
  TH1F* h_el_d0_cmid = new TH1F("h_el_d0_cmid","d0 of chargeMisID electrons",1000,0,5);

  TH1F* h_el_dZ_np = new TH1F("h_el_dZ_np","dZ of non-prompt ttbar electrons",1000,0,5);
  TH1F* h_el_dZ_pttb = new TH1F("h_el_dZ_pttb","dZ of prompt ttbar electrons",1000,0,5);
  TH1F* h_el_dZ_lhsig = new TH1F("h_el_dZ_lhsig","dZ of prompt LH signal electrons",1000,0,5);
  TH1F* h_el_dZ_rhsig = new TH1F("h_el_dZ_rhsig","dZ of prompt RH signal electrons",1000,0,5);
  TH1F* h_el_dZ_cmid = new TH1F("h_el_dZ_cmid","dZ of chargeMisID electrons",1000,0,5);

  TH1F* h_el_SIP3D_np = new TH1F("h_el_SIP3D_np","SIP3D of non-prompt ttbar electrons",1000,0,5);
  TH1F* h_el_SIP3D_pttb = new TH1F("h_el_SIP3D_pttb","SIP3D of prompt ttbar electrons",1000,0,5);
  TH1F* h_el_SIP3D_lhsig = new TH1F("h_el_SIP3D_lhsig","SIP3D of prompt LH signal electrons",1000,0,5);
  TH1F* h_el_SIP3D_rhsig = new TH1F("h_el_SIP3D_rhsig","SIP3D of prompt RH signal electrons",1000,0,5);
  TH1F* h_el_SIP3D_cmid = new TH1F("h_el_SIP3D_cmid","SIP3D of chargeMisID electrons",1000,0,5);


  TH1F* h_mu_d0_np = new TH1F("h_mu_d0_np","d0 of non-prompt ttbar muons",1000,0,5);
  TH1F* h_mu_d0_pttb = new TH1F("h_mu_d0_pttb","d0 of prompt ttbar muons",1000,0,5);
  TH1F* h_mu_d0_lhsig = new TH1F("h_mu_d0_lhsig","d0 of prompt LH signal muons",1000,0,5);
  TH1F* h_mu_d0_rhsig = new TH1F("h_mu_d0_rhsig","d0 of prompt RH signal muons",1000,0,5);


  TH1F* h_mu_dZ_np = new TH1F("h_mu_dZ_np","dZ of non-prompt ttbar muons",1000,0,5);
  TH1F* h_mu_dZ_pttb = new TH1F("h_mu_dZ_pttb","dZ of prompt ttbar muons",1000,0,5);
  TH1F* h_mu_dZ_lhsig = new TH1F("h_mu_dZ_lhsig","dZ of prompt LH signal muons",1000,0,5);
  TH1F* h_mu_dZ_rhsig = new TH1F("h_mu_dZ_rhsig","dZ of prompt RH signal muons",1000,0,5);

  TH1F* h_mu_SIP3D_np = new TH1F("h_mu_SIP3D_np","SIP3D of non-prompt ttbar muons",1000,0,5);
  TH1F* h_mu_SIP3D_pttb = new TH1F("h_mu_SIP3D_pttb","SIP3D of prompt ttbar muons",1000,0,5);
  TH1F* h_mu_SIP3D_lhsig = new TH1F("h_mu_SIP3D_lhsig","SIP3D of prompt LH signal muons",1000,0,5);
  TH1F* h_mu_SIP3D_rhsig = new TH1F("h_mu_SIP3D_rhsig","SIP3D of prompt RH signal muons",1000,0,5);


  bool mc = true;

  //ttbar tree reader
  TreeReader* tr_ttb = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Nov17/ljmet_trees/ljmet_TTBar_ext1.root",mc);
  //lh tree reader
  TreeReader* tr_lh = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Nov17/ljmet_trees/ljmet_X53X53m700LH_Inc.root",mc);
  //rh tree reader
  TreeReader* tr_rh = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Nov17/ljmet_trees/ljmet_X53X53m700RH_Inc.root",mc);
  //rh tree reader
  TreeReader* tr_cmid = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Nov17/ljmet_trees/ljmet_Data_All.root",!mc);

  
  int nEntries_ttb = tr_ttb->tree->GetEntries();
  int nEntries_lh = tr_lh->tree->GetEntries();
  int nEntries_rh = tr_rh->tree->GetEntries();
  int nEntries_cmid = tr_cmid->tree->GetEntries();


  //first do signal since easiest
  for(int ient=0; ient< nEntries_lh; ient++){

    tr_lh->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries_ttb<<" LH signal events"<<std::endl;
    //loop over electrons
    for(unsigned int i=0; i<tr_lh->allElectrons.size();i++){
      TElectron* iel = tr_lh->allElectrons.at(i);
      //skip if pT less than 30 GeV
      if(iel->pt <30) continue;
      //skip if not tight
      if( ! (iel->mvaTightRCIso()) ) continue;
      h_el_d0_lhsig->Fill(fabs(iel->d0));
      h_el_dZ_lhsig->Fill(fabs(iel->dZ));
      h_el_SIP3D_lhsig->Fill(fabs(iel->SIP3d));
    }
    
    for(unsigned int i=0; i<tr_lh->allMuons.size();i++){
      TMuon* imu = tr_lh->allMuons.at(i);
      //skip if pT less than 30 GeV
      if(imu->pt <30) continue;
      //skip if not tight
      if( ! (imu->cutBasedTight()) ) continue;
      h_mu_d0_lhsig->Fill(fabs(imu->dxy));
      h_mu_dZ_lhsig->Fill(fabs(imu->dz));
      h_mu_SIP3D_lhsig->Fill(fabs(imu->SIP3d));
    }

  }


    //first do signal since easiest
  for(int ient=0; ient< nEntries_rh; ient++){

    tr_rh->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries_ttb<<" RH signal events"<<std::endl;
    //loop over electrons
    for(unsigned int i=0; i<tr_rh->allElectrons.size();i++){
      TElectron* iel = tr_rh->allElectrons.at(i);
      //skip if pT less than 30 GeV
      if(iel->pt <30) continue;
      //skip if not tight
      if( ! (iel->mvaTightRCIso()) ) continue;
      h_el_d0_rhsig->Fill(fabs(iel->d0));
      h_el_dZ_rhsig->Fill(fabs(iel->dZ));
      h_el_SIP3D_rhsig->Fill(fabs(iel->SIP3d));
    }

    for(unsigned int i=0; i<tr_rh->allMuons.size();i++){
      TMuon* imu = tr_rh->allMuons.at(i);
      //skip if pT less than 30 GeV
      if(imu->pt <30) continue;
      //skip if not tight
      if( ! (imu->cutBasedTight()) ) continue;
      h_mu_d0_rhsig->Fill(fabs(imu->dxy));
      h_mu_dZ_rhsig->Fill(fabs(imu->dz));
      h_mu_SIP3D_rhsig->Fill(fabs(imu->SIP3d));
    }

  }


  //now ttbar
  for(int ient=0; ient < nEntries_ttb; ient++){

    tr_ttb->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries_ttb<<" ttbar events"<<std::endl;
    //loop over electrons
    for(unsigned int i=0; i<tr_ttb->allElectrons.size(); i++){
      TElectron* iel = tr_ttb->allElectrons.at(i);
      //skip if pT less than 30 GeV
      if(iel->pt <30) continue;
      //skip if not tight
      if(! (iel->mvaTightRCIso()) ) continue;
      //get matched genParticle
      TGenParticle* gp = getMatchedGenParticle(iel, tr_ttb->genParticles);
      //fill histograms for prompt electrons
      if(fabs(gp->id)==11 && ( gp->isPrompt || gp->isFromPromptTau) ){
	h_el_d0_pttb->Fill(fabs(iel->d0));
	h_el_dZ_pttb->Fill(fabs(iel->dZ));
	h_el_SIP3D_pttb->Fill(fabs(iel->SIP3d));
      }
      //fill for nonprompt/fake electrons
      else{
	h_el_d0_np->Fill(fabs(iel->d0));
	h_el_dZ_np->Fill(fabs(iel->dZ));
	h_el_SIP3D_np->Fill(fabs(iel->SIP3d));
      }
    }//end loop over electrons


    for(unsigned int i=0; i<tr_ttb->allMuons.size();i++){
      TMuon* imu = tr_ttb->allMuons.at(i);
      //skip if pT less than 30 GeV
      if(imu->pt <30) continue;
      //skip if not tight
      if(! imu->cutBasedTight() ) continue;
      //get matched genParticle
      TGenParticle* gp = getMatchedGenParticle(imu, tr_ttb->genParticles);
      //fill histograms for prompt electrons
      if(fabs(gp->id)==13 && ( gp->isPrompt || gp->isFromPromptTau) ){
	h_mu_d0_pttb->Fill(fabs(imu->dxy));
	h_mu_dZ_pttb->Fill(fabs(imu->dz));
	h_mu_SIP3D_pttb->Fill(fabs(imu->SIP3d));
      }
      //fill for nonprompt/fake electrons
      else{
	h_mu_d0_np->Fill(fabs(imu->dxy));
	h_mu_dZ_np->Fill(fabs(imu->dz));
	h_mu_SIP3D_np->Fill(fabs(imu->SIP3d));
      }


    }



  }//end event loop for ttbar

  //now loop over chargeMisID
  for(int ient=0; ient< nEntries_cmid; ient++){
    tr_cmid->GetEntry(ient);
    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries_cmid<<" charge misID events"<<std::endl;

    //make good electrons
    std::vector<TElectron*> goodElectrons;
    for(unsigned int i=0; i< tr_cmid->allElectrons.size(); i++){
      TElectron* iel = tr_cmid->allElectrons.at(i);
      if(iel->mvaTightRCIso()) goodElectrons.push_back(iel);
    }
    
    //make os electron pair from highest pT first
    std::vector<TElectron*> OSElectrons;
    bool foundpair = false;
    for(unsigned int i=0; i<goodElectrons.size();i++){
      TElectron* iel = goodElectrons.at(i);
      for(unsigned int j =i+1; j<goodElectrons.size(); j++){
	TElectron* jel = goodElectrons.at(j);
	if(iel->charge!=jel->charge){	 
	  OSElectrons.push_back(iel);OSElectrons.push_back(jel);	  
	  foundpair=true;
	  break;
	}
      }//end subloop over electrons
      if(foundpair) break;
    }//end loop over electrons

    //skip events where I didn't find pair;
    if(OSElectrons.size()<2) continue;
    TElectron* el1 = OSElectrons.at(0);
    TElectron* el2 = OSElectrons.at(1);
    float pairMass = (el1->lv + el2->lv).M();
    //skip events within 15 GeV of pair mass
    if( fabs(91.1-pairMass) <15) continue;
    
    //now fill histograms
    h_el_d0_cmid->Fill( fabs(el1->d0)); h_el_d0_cmid->Fill(fabs(el2->d0));
    h_el_dZ_cmid->Fill( fabs(el1->dZ)); h_el_dZ_cmid->Fill(fabs(el2->dZ));
    h_el_SIP3D_cmid->Fill( fabs(el1->SIP3d)); h_el_SIP3D_cmid->Fill(fabs(el2->SIP3d));

  }//end event loop for charge misID

  //write histograms to file
  fout->Write();
  fout->Close();

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

std::vector<TLepton*> makeOSLeptonsForDY(std::vector<TLepton*> leptons){

  std::vector<TLepton*> vSSLep;

  //leptons is ordered by pt so take leading two leptons
  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    TLepton* lep1 = leptons.at(uilep);
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      TLepton* lep2 = leptons.at(ujlep);
      //if both are muons don't save pair
      if(lep1->isMu && lep2->isMu) continue;
      if(lep1->charge != lep2->charge){
	vSSLep.push_back(lep1);
	vSSLep.push_back(lep2);
      }
    }
  }



  return vSSLep;

}

TGenParticle* getMatchedGenParticle(TMuon* mu, std::vector<TGenParticle*> genParticles){


  TGenParticle* gp=0;

  bool nearbyMu = false;

  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    float drtemp = pow( pow( mu->eta - genParticle->eta, 2 ) + pow( mu->phi - genParticle->phi, 2), 0.5);
    //std::cout<<"gen particle "<<igen<< " of "<<genParticles.size()<<" with id: "<< genParticle->id<<" and status: "<<genParticle->status<<" and mother: "<<genParticle->motherId<<" and dR: "<<drtemp<<std::endl;
    if(drtemp < dR){
      dR = drtemp;
      gp=genParticle;
    }
    if(drtemp<0.1 && fabs(genParticle->id)==13 && genParticle->status==1) nearbyMu = true;
  }

  if(!nearbyMu) return gp;
  else{
    //reset dr
    dR=999;
    for(unsigned int igen=0; igen<genParticles.size(); igen++){
      TGenParticle* genParticle = genParticles.at(igen);
      if( fabs(genParticle->id)!=13 || genParticle->status!=1) continue; //only loop over final state muons
      float drtemp = pow( pow( mu->eta - genParticle->eta, 2 ) + pow( mu->phi - genParticle->phi, 2), 0.5);
      if(drtemp < dR){
	dR = drtemp;
	gp=genParticle;
      }
      if(drtemp<0.1 && fabs(genParticle->id)==13 && genParticle->status==1) nearbyMu = true;
    }
  
  }

  return gp;

}
