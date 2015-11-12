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
std::vector<TLepton*> makeLeptons(std::vector<TElectron*> electrons, bool mc, bool FiftyNs, std::string ID);

//A script to get the prompt rate for electrons and muons. Usage is ./ChargeMisID.o <Data,MC> <El,Mu> 

int main(int argc, char* argv[]){

  if(argc!=4){
    std::cout<<"Need to specify whether running on Data or MC and whether 25 or 50ns as well as the ID. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns ID \n"
	     <<"./ChargeMisID.o Data 25ns ID \n"
	     <<"./ChargeMisID.o MC 50ns ID \n"
	     <<"./ChargeMisID.o MC 25ns ID \n";
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];
  std::string ID = argv[3];

  bool correctusage=false;
  if(argc==4 && (argv1.find("Data")!=std::string::npos || argv1.find("MC")!=std::string::npos ) && (argv2.find("25ns")!=std::string::npos || argv2.find("50ns")!=std::string::npos) ) correctusage=true;
  if(!correctusage){
    std::cout<<"Need to specify whether running on Data or MC and 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns ID \n"
	     <<"./ChargeMisID.o Data 25ns ID \n"
	     <<"./ChargeMisID.o MC 50ns ID \n"
	     <<"./ChargeMisID.o MC 25ns ID \n";
    return 0;
  }

  //get filename based on Data/MC
  std::string filename;
  bool data;
  bool FiftyNS;

  if(argv1=="Data" && argv2=="50ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Run2015B/ljmet_trees/ljmet_Data_ElEl.root"; data=true; FiftyNS=true;}
  else  if(argv1=="Data" && argv2=="25ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/ObjectReview/ljmet_trees/ljmet_Data_ElEl.root"; data=true; FiftyNS=false;}
  else if(argv1=="MC" && argv2=="50ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/50ns/ljmet_trees/ljmet_DYJets.root"; data=false; FiftyNS=true;}
  else if(argv1=="MC" && argv2=="25ns") {filename="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/ObjectReview/ljmet_trees/ljmet_DYJets.root"; data=false; FiftyNS=false;}
  else{
    std::cout<<"Need to specify whether running on Data or MC and 25 or 50ns. The four possible ways of running are\n"
	     <<"./ChargeMisID.o Data 50ns \n"
	     <<"./ChargeMisID.o Data 25ns \n"
	     <<"./ChargeMisID.o MC 50ns \n"
	     <<"./ChargeMisID.o MC 25ns \n";
  }

  //make filename for output root file
  std::string outname;
  if(data)outname="ChargeMisID_Data_Run2015D_Electrons_"+ID+".root"; 
  else outname="ChargeMisID_MC_Electrons_"+ID+".root"; 


  //open output file
  TFile* fout= new TFile(outname.c_str(),"RECREATE");

  //get tree reader to read in data
  TreeReader* tr= new TreeReader(filename.c_str(),!data);
  TTree* t=tr->tree;

  //initialize needed histograms
  TH1F* ptNumHist = new TH1F("ptNumHist","p_{T} of Same Sign Leptons",20,0,600);
  TH1F* ptDenHist = new TH1F("ptDenHist","p_{T} of All Leptons",20,0,600);
  TH1F* etaAllHist = new TH1F("etaAllHist","#eta of All Leptons",15,-3,3);
  TH1F* etaNumHist = new TH1F("etaNumHist","#eta of Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist = new TH1F("etaDenHist","#eta of All Leptons",15,-3,3);

  TH1F* etaNumHist_lpt = new TH1F("etaNumHist_lpt","#eta of low pT Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist_lpt = new TH1F("etaDenHist_lpt","#eta of low pT Leptons",15,-3,3);

  TH1F* etaNumHist_hpt = new TH1F("etaNumHist_hpt","#eta of High pT Same Sign Leptons",15,-3,3);
  TH1F* etaDenHist_hpt = new TH1F("etaDenHist_hpt","#eta of High pT Leptons",15,-3,3);

  TH1F* massNumHist = new TH1F("massNumHist","M_{ll} of Same Sign Leptons",50,0,150);
  TH1F* massDenHist = new TH1F("massDenHist","M_ll} of All Leptons",50,0,150);

  //get number of entries and start event loop
  int nEntries = t->GetEntries();
  for(int ient=0; ient<nEntries; ient++){

    tr->GetEntry(ient);

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    for(std::vector<TElectron*>::size_type iel=0; iel<tr->goodElectrons.size();iel++){
      etaAllHist->Fill( (tr->goodElectrons).at(iel)->eta,tr->MCWeight);
    }

    //make vector of leptons
    std::vector<TLepton*> leptons = makeLeptons(tr->allElectrons,!data,FiftyNS,ID);

    //skip if didn't find at least two tight leptons
    if(leptons.size()<2) continue;

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
	  massDiff = zmass-pairmass;
	  lep1=leptons.at(ilep);
	  lep2=leptons.at(jlep);
	}
      }//end second loop over leptons
    }//end loop over leptons

    //check that leptons are in Zpeak
    bool zpeak= fabs(massDiff)<10 ? true : false;

    //fill denominator
    massDenHist->Fill(zmass+massDiff,tr->MCWeight);

    if(!zpeak) continue;

    //now fill histograms
    if(lep1->charge == lep2->charge){
      massNumHist->Fill(zmass+massDiff,tr->MCWeight);
      ptNumHist->Fill(lep1->pt,tr->MCWeight);
      ptNumHist->Fill(lep2->pt,tr->MCWeight);
      etaNumHist->Fill(lep1->eta,tr->MCWeight);
      etaNumHist->Fill(lep2->eta,tr->MCWeight);
      if(lep1->pt>100 || lep2->pt>100){
	etaNumHist_hpt->Fill(lep1->eta,tr->MCWeight);
	etaNumHist_hpt->Fill(lep2->eta,tr->MCWeight);
      }
      else{
	etaNumHist_lpt->Fill(lep1->eta,tr->MCWeight);
	etaNumHist_lpt->Fill(lep2->eta,tr->MCWeight);
      }
    }

    //fill denominator
    ptDenHist->Fill(lep1->pt,tr->MCWeight);
    ptDenHist->Fill(lep2->pt,tr->MCWeight);
    etaDenHist->Fill(lep1->eta,tr->MCWeight);
    etaDenHist->Fill(lep2->eta,tr->MCWeight);
    if(lep1->pt>100 || lep2->pt>100){
      etaDenHist_hpt->Fill(lep1->eta,tr->MCWeight);
      etaDenHist_hpt->Fill(lep2->eta,tr->MCWeight);
    }
    else{
      etaDenHist_lpt->Fill(lep1->eta,tr->MCWeight);
      etaDenHist_lpt->Fill(lep2->eta,tr->MCWeight);
    }
  }//end event loop

  //save weights 
  etaNumHist->Sumw2();
  etaDenHist->Sumw2();
  etaNumHist_hpt->Sumw2();
  etaDenHist_hpt->Sumw2();
  etaNumHist_lpt->Sumw2();
  etaDenHist_lpt->Sumw2();
  ptNumHist->Sumw2();
  ptDenHist->Sumw2();
  massNumHist->Sumw2();
  massDenHist->Sumw2();

  //scale num hists by 1/2 (except mass)
  etaNumHist->Scale(0.5);
  etaNumHist_lpt->Scale(0.5);
  etaNumHist_hpt->Scale(0.5);
  ptNumHist->Scale(0.5);

  //write file now that histograms have been filled
  fout->Append(ptNumHist);
  fout->Append(ptDenHist);
  fout->Append(etaAllHist);
  fout->Append(etaNumHist);
  fout->Append(etaDenHist);
  fout->Append(etaNumHist_hpt);
  fout->Append(etaDenHist_hpt);
  fout->Append(etaNumHist_lpt);
  fout->Append(etaDenHist_lpt);
  fout->Append(massNumHist);
  fout->Append(massDenHist);
  //make tgraphs for promptrate
  TGraphAsymmErrors* ptGraph = new TGraphAsymmErrors(ptNumHist,ptDenHist);
  TGraphAsymmErrors* etaGraph = new TGraphAsymmErrors(etaNumHist,etaDenHist);
  //write the tgraphs
  fout->Append(ptGraph);
  fout->Append(etaGraph);

  //make hists of rate
  TH1F* rateEta = (TH1F*) etaNumHist->Clone();
  rateEta->Divide(etaDenHist);
  TH1F* ratePt = (TH1F*) ptNumHist->Clone();
  ratePt->Divide(ptDenHist);
  TH1F* rateEta_lpt = (TH1F*)etaNumHist_lpt->Clone();
  rateEta_lpt->Divide(etaDenHist_lpt);
  TH1F* rateEta_hpt = (TH1F*)etaNumHist_hpt->Clone();
  rateEta_hpt->Divide(etaDenHist_hpt);
  fout->Append(rateEta);
  fout->Append(rateEta_lpt);
  fout->Append(rateEta_hpt);
  fout->Append(ratePt);

  fout->Write();




  return 0;
}


std::vector<TLepton*> makeLeptons(std::vector<TElectron*> electrons, bool mc, bool FiftyNs, std::string ID){

  std::vector<TLepton*> Leptons;

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
    if(ID=="CBTightRC"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MCRC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MCRC();
    }
    else if(ID=="CBLooseRC"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MCRC();
      iLep->Loose=true;
    }
    else if(ID=="MVATightNew"){
      iLep->Tight=iel->mvaTightNew();
      iLep->Loose=iel->mvaLooseNew();
    }
    else if(ID=="MVATightNewRC"){
      iLep->Tight=iel->mvaTightNewRC();
      iLep->Loose=iel->mvaLooseNewRC();
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
    else if(ID=="MVATightCC"){
      iLep->Tight=iel->mvaTightCCIso();
      iLep->Loose=iel->mvaLooseCCIso();
    }
    else if(ID=="MVATightCCNoIso"){
      iLep->Tight=iel->mvaTightCC();
      iLep->Loose=iel->mvaLooseCC();
    }
    else if(ID=="MVALooseCC"){
      iLep->Tight=iel->mvaLooseCCIso();
      iLep->Loose=true;
    }
    else if(ID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }  
    else if(ID=="MVATightRC"){
      iLep->Tight=iel->mvaTightRCIso();
      iLep->Loose=iel->mvaLooseRCIso();
    }
    else if(ID=="MVALooseRC"){
      iLep->Tight=iel->mvaLooseRCIso();
      iLep->Loose=true;
    }
    else if(ID=="SUSYTight"){
      iLep->Tight=iel->susyTight();
      iLep->Loose=iel->susyLoose();
    }
    else if(ID=="SUSYLoose"){
	iLep->Tight=iel->susyLoose();
	iLep->Loose=true;
    }
    else if(ID=="SUSYTightRC"){
      iLep->Tight=iel->susyTightRC();
      iLep->Loose=iel->susyLooseRC();
    }      
    iLep->isMu = false;
    iLep->isEl = true;
    //only save if tight
    if(iLep->Tight){
      //apply pt cut
      if(iLep->pt>30) Leptons.push_back(iLep);
    }
  }


  return Leptons;
 
}
