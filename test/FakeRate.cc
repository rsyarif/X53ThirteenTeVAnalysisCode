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
std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons, std::string ID);
bool ZVetoCheck(TLepton* lepton, std::vector<TJet*> jets);
bool AwayJetCheck(TLepton* lepton, std::vector<TJet*> jets);

int main(int argc, char* argv[]){

  //example usage: ./FakeRate.o Data Electrons

  if(argc!=3){
    std::cout<<"Error! You must specify whether running on 'Data' of 'MC' as option as well as electrons or muons"<<std::endl;
    return 0;
  }

  std::string argv1 = argv[1];
  std::string argv2 = argv[2];

  if(argv1.find("Data")==std::string::npos && argv1.find("MC")==std::string::npos){
    std::cout<<"Error! You must specify whether running on 'Data' of 'MC' as option"<<std::endl;
    return 0;
  }

  //now get boolean for data or mc
  bool data=false;
  if(argv1.find("Data")!=std::string::npos) data=true;

  //boolean for channel
  bool MuonChannel=false;
  if(argv2.find("Muons")!=std::string::npos) MuonChannel=true;


  //make output file
  std::vector<std::string> outname;
  if(data){
    if(MuonChannel) outname.push_back("FakeRate_Data_Muons.root");
    else outname.push_back("FakeRate_Data_Electrons.root");
  }

  else{
    if(MuonChannel){
      outname.push_back("FakeRate_MC_Muons_HT100To200.root");
      outname.push_back("FakeRate_MC_Muons_HT200To300.root");
      outname.push_back("FakeRate_MC_Muons_HT300To500.root");
      outname.push_back("FakeRate_MC_Muons_HT500To700.root");
      outname.push_back("FakeRate_MC_Muons_HT700To1000.root");
      outname.push_back("FakeRate_MC_Muons_HT1000To1500.root");
      outname.push_back("FakeRate_MC_Muons_HT1500To2000.root");
      outname.push_back("FakeRate_MC_Muons_HT2000ToInf.root");
    }
    else{
      outname.push_back("FakeRate_MC_Electrons_HT100To200.root");
      outname.push_back("FakeRate_MC_Electrons_HT200To300.root");
      outname.push_back("FakeRate_MC_Electrons_HT300To500.root");
      outname.push_back("FakeRate_MC_Electrons_HT500To700.root");
      outname.push_back("FakeRate_MC_Electrons_HT700To1000.root");
      outname.push_back("FakeRate_MC_Electrons_HT1000To1500.root");
      outname.push_back("FakeRate_MC_Electrons_HT1500To2000.root");
      outname.push_back("FakeRate_MC_Electrons_HT2000ToInf.root");
    }
  }




  //get correct file
  std::vector<std::string> filenames;
  if(argv1.find("Data")!=std::string::npos) {
    if(MuonChannel) filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Run2015B/FakeRateTrees/ljmet_trees/ljmet_FakeRate_Mu.root");
    else if(!MuonChannel) filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Run2015B/FakeRateTrees/ljmet_trees/ljmet_FakeRate_El.root");
  }
  else{
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT100To200.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT200To300.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT300To500.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT500To700.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT700To1000.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT1000To1500.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT1500To2000.root");
    filenames.push_back("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct08/FakeRate/ljmet_trees/ljmet_tree_QCDHT2000ToInf.root");
  }

  for(unsigned int i =0; i<filenames.size(); i++){
    
    TFile* fout = new TFile(outname.at(i).c_str(),"RECREATE");
    //get tree reader to read in data
    TreeReader* tr= new TreeReader(filenames.at(i).c_str(),!data);
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
      std::vector<TLepton*> leptons = makeLeptons(tr->allMuons,tr->allElectrons,MuonChannel, ID);
	
      //veto on events with more than one lepton or no leptons
      if((leptons.size()==0) || (leptons.size() >1) ) continue;
      //now just take the lepton remaining
      TLepton* lep = leptons.at(0);
      
      //make sure not much met in event to veto on leptons from Ws
      if(tr->MET > 25) continue;
      
      //check transverse mass is less than 25 GeV
      
      float et = tr->MET+lep->energy;
      float pt1y = lep->pt*sin(lep->phi);
      float pt1x = lep->pt*cos(lep->phi);
      float pt2y = tr->MET*sin(tr->MET_phi);
      float pt2x = tr->MET*cos(tr->MET_phi);
      float mT = pow(et,2) - pow(lep->pt,2) - pow(tr->MET,2) - 2*(pt1y*pt2y - pt1x*pt2x);
      mT = pow(mT, 0.5);
      if(mT>25) continue;
      
      //search through jet collection to check for jet mass
      bool Zveto = ZVetoCheck(lep,tr->allAK4Jets);
      if(Zveto) continue;
      
      //check for away jet
      bool awayJet = AwayJetCheck(lep,tr->allAK4Jets);
      if(!awayJet) continue;
      
      //Now just fill histograms
      etaDenHist->Fill(lep->eta); ptDenHist->Fill(lep->pt);
      if(lep->Tight){etaNumHist->Fill(lep->eta);ptNumHist->Fill(lep->pt);}
	
    }//end event loop
    
    fout->Append(ptNumHist);
    fout->Append(ptDenHist);
    fout->Append(etaNumHist);
    fout->Append(etaDenHist);
    
    TGraphAsymmErrors* ptgraph = new TGraphAsymmErrors(ptNumHist,ptDenHist);
    TGraphAsymmErrors* etagraph = new TGraphAsymmErrors(etaNumHist,etaDenHist);
    
    fout->Append(ptgraph);
    fout->Append(etagraph);
    fout->Write();
    fout->Close();
  }//end loop over filenames
}

std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, bool Muons, std::string ID){

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
      //only save if at least loose
      if(iLep->Tight || iLep->Loose){
	//apply pt cut
	if(iLep->pt>25 && iLep->pt<35) Leptons.push_back(iLep);
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
      //only save if at least loose
      if(iLep->Tight || iLep->Loose){
	//apply pt cut
	if(iLep->pt>25 && iLep->pt<35) Leptons.push_back(iLep);
      }
    }
  }

  return Leptons;

}

bool ZVetoCheck(TLepton* lep, std::vector<TJet*> jets){



  float diff=999;
  for(std::vector<TJet*>::size_type i=0; i< jets.size(); i++){
    TJet* ijet = jets.at(i);
    float tempmass = (lep->lv + ijet->lv).M();
    if( fabs(tempmass-91.1) <diff){
      diff = fabs(tempmass-91.1);

    }
  }

  bool veto=false;
  if(diff<15) veto=true;

  return veto;

}


bool AwayJetCheck(TLepton* lep, std::vector<TJet*> jets){

  bool awayJet=false;

  for(std::vector<TJet*>::size_type i=0; i<jets.size();i++){
    TJet* ijet = jets.at(i);
    float dr = pow( pow(lep->eta - ijet->eta,2) + pow(lep->phi - ijet->phi,2) , 0.5);
    if(ijet->pt>40 && dr>1.0){ awayJet=true; break;}
  }

  return awayJet;
}
