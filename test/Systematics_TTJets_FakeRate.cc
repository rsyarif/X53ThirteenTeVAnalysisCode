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
bool matchToGenLep(TMuon* mu, std::vector<TGenParticle*> genParticles);
bool matchToGenLep(TElectron* el, std::vector<TGenParticle*> genParticles);
TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles);
TGenParticle* getMatchedGenParticle(TMuon* mu, std::vector<TGenParticle*> genParticles);


int main(int argc, char* argv[]){

  if(argc!=4){
    std::cout<<"Need to specify electrons or muons and ID used! Exiting..."<<std::endl;
    return 0; 
  }

  bool Muons;
  std::string channel = argv[1];
  if(channel=="Muons") Muons=true;
  else Muons=false;

  std::string elID = argv[2];
  std::string muID = argv[3];

  bool mc=true;
  
  TreeReader* tr = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/ObjectReview/ljmet_trees/ljmet_TTJets.root",mc);
  TTree* t = tr->tree;

  TFile* outfile = new TFile("FakeRate_TTJets_MCTruth.root","RECREATE");

  TH1F* elNumHist_lpt = new TH1F("elNumHist_lpt","elNumHist_lpt",5,0,5);
  TH1F* elDenHist_lpt = new TH1F("elDenHist_lpt","elDenHist_lpt",5,0,5);
  TH1F* elNumHist_hpt = new TH1F("elNumHist_hpt","elNumHist_hpt",5,0,5);
  TH1F* elDenHist_hpt = new TH1F("elDenHist_hpt","elDenHist_hpt",5,0,5);
  TH1F* elNumHist_all = new TH1F("elNumHist_all","elNumHist_all",5,0,5);
  TH1F* elDenHist_all = new TH1F("elDenHist_all","elDenHist_all",5,0,5);

  TH1F* muNumHist_lpt = new TH1F("muNumHist_lpt","muNumHist_lpt",5,0,5);
  TH1F* muDenHist_lpt = new TH1F("muDenHist_lpt","muDenHist_lpt",5,0,5);
  TH1F* muNumHist_hpt = new TH1F("muNumHist_hpt","muNumHist_hpt",5,0,5);
  TH1F* muDenHist_hpt = new TH1F("muDenHist_hpt","muDenHist_hpt",5,0,5);
  TH1F* muNumHist_all = new TH1F("muNumHist_all","muNumHist_all",5,0,5);
  TH1F* muDenHist_all = new TH1F("muDenHist_all","muDenHist_all",5,0,5);


  //set bin labels
  elNumHist_lpt->GetXaxis()->SetBinLabel(1,"Light Quarks");elNumHist_hpt->GetXaxis()->SetBinLabel(1,"Light Quarks");elNumHist_all->GetXaxis()->SetBinLabel(1,"Light Quarks");
  elNumHist_lpt->GetXaxis()->SetBinLabel(2,"Charm Quarks");elNumHist_hpt->GetXaxis()->SetBinLabel(2,"Charm Quarks");elNumHist_all->GetXaxis()->SetBinLabel(2,"Charm Quarks");
  elNumHist_lpt->GetXaxis()->SetBinLabel(3,"Bottom Quarks");elNumHist_hpt->GetXaxis()->SetBinLabel(3,"Bottom Quarks");elNumHist_all->GetXaxis()->SetBinLabel(3,"Bottom Quarks");
  elNumHist_lpt->GetXaxis()->SetBinLabel(4,"Misc.");elNumHist_hpt->GetXaxis()->SetBinLabel(4,"Misc.");elNumHist_all->GetXaxis()->SetBinLabel(4,"Misc.");
  elNumHist_lpt->GetXaxis()->SetBinLabel(5,"Unmatched");elNumHist_hpt->GetXaxis()->SetBinLabel(5,"Unmatched");elNumHist_all->GetXaxis()->SetBinLabel(5,"Unmatched");

  muNumHist_lpt->GetXaxis()->SetBinLabel(1,"Light Quarks");muNumHist_hpt->GetXaxis()->SetBinLabel(1,"Light Quarks");muNumHist_all->GetXaxis()->SetBinLabel(1,"Light Quarks");
  muNumHist_lpt->GetXaxis()->SetBinLabel(2,"Charm Quarks");muNumHist_hpt->GetXaxis()->SetBinLabel(2,"Charm Quarks");muNumHist_all->GetXaxis()->SetBinLabel(2,"Charm Quarks");
  muNumHist_lpt->GetXaxis()->SetBinLabel(3,"Bottom Quarks");muNumHist_hpt->GetXaxis()->SetBinLabel(3,"Bottom Quarks");muNumHist_all->GetXaxis()->SetBinLabel(3,"Bottom Quarks");
  muNumHist_lpt->GetXaxis()->SetBinLabel(4,"Misc.");muNumHist_hpt->GetXaxis()->SetBinLabel(4,"Misc.");muNumHist_all->GetXaxis()->SetBinLabel(4,"Misc.");
  muNumHist_lpt->GetXaxis()->SetBinLabel(5,"Unmatched");muNumHist_hpt->GetXaxis()->SetBinLabel(5,"Unmatched");muNumHist_all->GetXaxis()->SetBinLabel(5,"Unmatched");

  int nEntries = t->GetEntries();

  for(int ient=0; ient < nEntries; ient++){
    //for(int ient=0; ient < 200; ient++){

    tr->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    std::vector<TElectron*> electrons = tr->allElectrons;

    for(unsigned int i=0; i<electrons.size();i++){
      TElectron* iel = electrons.at(i);
      bool loose = false;
      bool tight = false;
      if(elID=="MVATightRC"){
	loose = iel->mvaLooseRCIso();
	tight = iel->mvaTightRCIso();
      }
      else{
	std::cout<<"Didn't pick analysis ID! Are you sure? Exiting so you can think about it..."<<std::endl;
	return 0;
      }

      //skip any with pt below 25 GeV
      if(iel->pt<25) continue;
      //skip if not at least loose
      if(!loose) continue;

      //make sure it is not matched to a gen electron
      bool matched = matchToGenLep(iel, tr->genParticles);
      if(matched) continue;
      TGenParticle* gp = getMatchedGenParticle(iel,tr->genParticles);	
      
      float dR = pow( pow(gp->eta - iel->eta,2) + pow(gp->phi - iel->phi,2), 0.5);
      std::cout<<"Closest Gen Particle Info: dR = "<<dR<<"; id = "<<gp->id<<"; status = "<<gp->status<<"; motherId = "<<gp->motherId<<std::endl;
      if(tight) std::cout<<"Electron passes tight ID with pT: "<<iel->pt<<" mva value: "<<iel->mvaValue<<" miniIso: "<<iel->miniIso<<std::endl;
      if(dR>0.3){//unmatched
	elDenHist_all->Fill(4.5);
	if(iel->pt>35) elDenHist_hpt->Fill(4.5);
	else elDenHist_lpt->Fill(4.5);
	if(tight){
	  elNumHist_all->Fill(4.5);
	  if(iel->pt>35) elNumHist_hpt->Fill(4.5);
	  else elNumHist_lpt->Fill(4.5);
	}
      
      }//end if about unmatched
      else{ 
	if(fabs(gp->id)==1 || fabs(gp->id)==2 || fabs(gp->id)==3){
	  elDenHist_all->Fill(0.5);	   
	  if(iel->pt>35) elDenHist_hpt->Fill(0.5);
	  else elDenHist_lpt->Fill(0.5);
	  if(tight){
	    elNumHist_all->Fill(0.5);
	    if(iel->pt>35) elNumHist_hpt->Fill(0.5);
	    else elNumHist_lpt->Fill(0.5);
	  }
	}/// end light quarks
	else if(fabs(gp->id)==4){
	  elDenHist_all->Fill(1.5);	   
	  if(iel->pt>35) elDenHist_hpt->Fill(1.5);
	  else elDenHist_lpt->Fill(1.5);
	  if(tight){
	    elNumHist_all->Fill(1.5);
	    if(iel->pt>35) elNumHist_hpt->Fill(1.5);
	    else elNumHist_lpt->Fill(1.5);
	  }
	}//end check on charm quarks

	else if(fabs(gp->id)==5){
	  elDenHist_all->Fill(2.5);	   
	  if(iel->pt>35) elDenHist_hpt->Fill(2.5);
	  else elDenHist_lpt->Fill(2.5);
	  if(tight){
	    elNumHist_all->Fill(2.5);
	    if(iel->pt>35) elNumHist_hpt->Fill(2.5);
	    else elNumHist_lpt->Fill(2.5);
	  }
	}//end check on bottom quarks
	else {
	  elDenHist_all->Fill(3.5);	   
	  if(iel->pt>35) elDenHist_hpt->Fill(3.5);
	  else elDenHist_lpt->Fill(3.5);
	  if(tight){
	    elNumHist_all->Fill(3.5);
	    if(iel->pt>35) elNumHist_hpt->Fill(3.5);
	    else elNumHist_lpt->Fill(3.5);
	  }
	}//end misc





      }//end check on matched
    }//electron loop

    std::vector<TMuon*> muons = tr->allMuons;
    for(unsigned int i=0; i<muons.size(); i++){
      TMuon* imu = muons.at(i);

      bool loose=false;
      bool tight=false;
      if(muID=="CBTight"){
	loose = imu->cutBasedLoose();
	tight = imu->cutBasedTight();
      }
      else{
	std::cout<<"Muon ID selected not the one used in analysis! Are you sure?? Exiting to let you think about it..."<<std::endl;
	return 0;
      }

      //skip any with pt below 25 GeV
      if(imu->pt<25) continue;
      //skip if not at least loose
      if(!loose) continue;

      //make sure it is not matched to a gen electron
      bool matched = matchToGenLep(imu, tr->genParticles);
      if(matched) continue;
      TGenParticle* gp = getMatchedGenParticle(imu,tr->genParticles);	
      
      float dR = pow( pow(gp->eta - imu->eta,2) + pow(gp->phi - imu->phi,2), 0.5);
      std::cout<<"Closest Gen Particle Info: dR = "<<dR<<"; id = "<<gp->id<<"; status = "<<gp->status<<"; motherId = "<<gp->motherId<<std::endl;
      if(tight) std::cout<<"Muon passes tight ID with pT: "<<imu->pt<<" relIso: "<<imu->relIso<<std::endl;
      if(dR>0.3){//unmatched
	muDenHist_all->Fill(4.5);
	if(imu->pt>35) muDenHist_hpt->Fill(4.5);
	else muDenHist_lpt->Fill(4.5);
	if(tight){
	  muNumHist_all->Fill(4.5);
	  if(imu->pt>35) muNumHist_hpt->Fill(4.5);
	  else muNumHist_lpt->Fill(4.5);
	}
      
      }//end if about unmatched
      else{
	if(fabs(gp->id)==1 || fabs(gp->id)==2 || fabs(gp->id)==3){
	  muDenHist_all->Fill(0.5);	   
	  if(imu->pt>35) muDenHist_hpt->Fill(0.5);
	  else muDenHist_lpt->Fill(0.5);
	  if(tight){
	    muNumHist_all->Fill(0.5);
	    if(imu->pt>35) muNumHist_hpt->Fill(0.5);
	    else muNumHist_lpt->Fill(0.5);
	  }
	}/// end light quarks
	else if(fabs(gp->id)==4){
	  muDenHist_all->Fill(1.5);	   
	  if(imu->pt>35) muDenHist_hpt->Fill(1.5);
	  else muDenHist_lpt->Fill(1.5);
	  if(tight){
	    muNumHist_all->Fill(1.5);
	    if(imu->pt>35) muNumHist_hpt->Fill(1.5);
	    else muNumHist_lpt->Fill(1.5);
	  }
	}//end check on charm quarks

	else if(fabs(gp->id)==5){
	  muDenHist_all->Fill(2.5);	   
	  if(imu->pt>35) muDenHist_hpt->Fill(2.5);
	  else muDenHist_lpt->Fill(2.5);
	  if(tight){
	    muNumHist_all->Fill(2.5);
	    if(imu->pt>35) muNumHist_hpt->Fill(2.5);
	    else muNumHist_lpt->Fill(2.5);
	  }
	}//end check on bottom quarks

	else{
	  muDenHist_all->Fill(3.5);	   
	  if(imu->pt>35) muDenHist_hpt->Fill(3.5);
	  else muDenHist_lpt->Fill(3.5);
	  if(tight){
	    muNumHist_all->Fill(3.5);
	    if(imu->pt>35) muNumHist_hpt->Fill(3.5);
	    else muNumHist_lpt->Fill(3.5);
	  }
	}//end misc



      }//end check on matched
    }//muon loop

      

  }//end event loop

  elNumHist_lpt->Divide(elDenHist_lpt);
  elNumHist_hpt->Divide(elDenHist_hpt);
  elNumHist_all->Divide(elDenHist_all);
  std::cout<<"Electron fake rate for pt 25-35 electrons: "<<elNumHist_lpt->GetBinContent(1)<<" +/- "<<elNumHist_lpt->GetBinError(1)<<std::endl;
  std::cout<<"Electron fake rate for pt>25 electrons: "<<elNumHist_hpt->GetBinContent(1)<<" +/- "<<elNumHist_hpt->GetBinError(1)<<std::endl;
  std::cout<<"Electron fake rate for all electrons: "<<elNumHist_all->GetBinContent(1)<<" +/- "<<elNumHist_all->GetBinError(1)<<std::endl;

  muNumHist_lpt->Divide(muDenHist_lpt);
  muNumHist_hpt->Divide(muDenHist_hpt);
  muNumHist_all->Divide(muDenHist_all);
  std::cout<<"Muon fake rate for pt 25-35 muons: "<<muNumHist_lpt->GetBinContent(1)<<" +/- "<<muNumHist_lpt->GetBinError(1)<<std::endl;
  std::cout<<"Muon fake rate for pt>25 muons: "<<muNumHist_hpt->GetBinContent(1)<<" +/- "<<muNumHist_hpt->GetBinError(1)<<std::endl;
  std::cout<<"Muon fake rate for all muons: "<<muNumHist_all->GetBinContent(1)<<" +/- "<<muNumHist_all->GetBinError(1)<<std::endl;


  elNumHist_lpt->Sumw2();
  elNumHist_hpt->Sumw2();
  elNumHist_all->Sumw2();
  elDenHist_lpt->Sumw2();
  elDenHist_hpt->Sumw2();
  elDenHist_all->Sumw2();

  muNumHist_lpt->Sumw2();
  muNumHist_hpt->Sumw2();
  muNumHist_all->Sumw2();
  muDenHist_lpt->Sumw2();
  muDenHist_hpt->Sumw2();
  muDenHist_all->Sumw2();

  outfile->Append(elNumHist_lpt);
  outfile->Append(elNumHist_hpt);
  outfile->Append(elNumHist_all);
  outfile->Append(elDenHist_lpt);
  outfile->Append(elDenHist_hpt);
  outfile->Append(elDenHist_all);

  outfile->Append(muNumHist_lpt);
  outfile->Append(muNumHist_hpt);
  outfile->Append(muNumHist_all);
  outfile->Append(muDenHist_lpt);
  outfile->Append(muDenHist_hpt);
  outfile->Append(muDenHist_all);
 
  outfile->Write();

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
  if(dR <0.3) return true;
  else return false;
  
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
  if(dR <0.3) return true;
  else return false;
  
}

TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles){


  TGenParticle* gp=0;


  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    float drtemp = pow( pow( el->eta - genParticle->eta, 2 ) + pow( el->phi - genParticle->phi, 2), 0.5);
    std::cout<<"gen particle "<<igen<< " of "<<genParticles.size()<<" with id: "<< genParticle->id<<" and dR: "<<drtemp<<std::endl;
    if(drtemp < dR){
      dR = drtemp;
      gp=genParticle;
    }
  }

  return gp;
}

TGenParticle* getMatchedGenParticle(TMuon* mu, std::vector<TGenParticle*> genParticles){


  TGenParticle* gp=0;


  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    float drtemp = pow( pow( mu->eta - genParticle->eta, 2 ) + pow( mu->phi - genParticle->phi, 2), 0.5);
    std::cout<<"gen particle "<<igen<< " of "<<genParticles.size()<<" with id: "<< genParticle->id<<" and status: "<<genParticle->status<<" and mother: "<<genParticle->motherId<<" and dR: "<<drtemp<<std::endl;
    if(drtemp < dR){
      dR = drtemp;
      gp=genParticle;
    }
  }

  return gp;
}
