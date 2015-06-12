#include "../interface/TreeMaker.h"
#include <assert.h>

//constructor
TreeMaker::TreeMaker(){}


//destructor
TreeMaker::~TreeMaker(){}

//Initialize tree
void TreeMaker::InitTree(std::string treename){
  tree = new TTree(treename.c_str(),treename.c_str());


  tree->Branch("Lep1Pt",&Lep1Pt_);

  tree->Branch("Lep1Eta",&Lep1Eta_);
  tree->Branch("Lep1Phi",&Lep1Phi_);
  tree->Branch("Lep1Energy",&Lep1Energy_);
  tree->Branch("Lep1Flavor",&Lep1Flavor_);
  tree->Branch("Lep1Charge",&Lep1Charge_);
  tree->Branch("Lep1Loose",&Lep1Loose_);
  tree->Branch("Lep1Tight",&Lep1Tight_);


  tree->Branch("Lep2Pt",&Lep2Pt_);
  tree->Branch("Lep2Eta",&Lep2Eta_);
  tree->Branch("Lep2Phi",&Lep2Phi_);
  tree->Branch("Lep2Energy",&Lep2Energy_);
  tree->Branch("Lep2Flavor",&Lep2Flavor_);
  tree->Branch("Lep2Charge",&Lep2Charge_);
  tree->Branch("Lep2Loose",&Lep2Loose_);
  tree->Branch("Lep2Tight",&Lep2Tight_);


  //tree->Branch("NTightLeptons",&NTightLeptons_);
  tree->Branch("nAK4Jets",&nAK4Jets_);

  tree->Branch("AK4HT",&AK4HT_);
  tree->Branch("MET",&MET_);

  tree->Branch("AK4Jet1Pt",&AK4Jet1Pt_);
  tree->Branch("AK4Jet1Eta",&AK4Jet1Eta_);
  tree->Branch("AK4Jet1Phi",&AK4Jet1Phi_);
  tree->Branch("AK4Jet1Energy",&AK4Jet1Energy_);

  tree->Branch("AK4Jet2Pt",&AK4Jet2Pt_);
  tree->Branch("AK4Jet2Eta",&AK4Jet2Eta_);
  tree->Branch("AK4Jet2Phi",&AK4Jet2Phi_);
  tree->Branch("AK4Jet2Energy",&AK4Jet2Energy_);  

  tree->Branch("DilepMass",&DilepMass_);
  tree->Branch("Channel",&nMu_);
}

void TreeMaker::FillTree(std::vector<TLepton*> vSSLep, std::vector<TJet*> AK4Jets, float HTtemp, float METtemp, float DilepMasstemp, int nMu){

  assert(vSSLep.size()>1);

  Lep1Pt_=vSSLep.at(0)->pt;
  Lep1Eta_=vSSLep.at(0)->eta;
  Lep1Phi_=vSSLep.at(0)->phi;
  Lep1Energy_=vSSLep.at(0)->energy;
  vSSLep.at(0)->isMu ? Lep1Flavor_=1 : Lep1Flavor_=0;

  Lep2Pt_=vSSLep.at(1)->pt;
  Lep2Eta_=vSSLep.at(1)->eta;
  Lep2Phi_=vSSLep.at(1)->phi;
  Lep2Energy_=vSSLep.at(1)->energy;
  vSSLep.at(1)->isMu ? Lep2Flavor_=1 : Lep2Flavor_=0;

  if(Lep2Pt_<20) std::cout<<"Lep2Pt "<<vSSLep.at(1)->pt<<std::endl;

  AK4HT_=HTtemp;
  MET_=METtemp;

  nAK4Jets_ = AK4Jets.size();

  if(nAK4Jets_>0){
    AK4Jet1Pt_=AK4Jets.at(0)->pt;    
    AK4Jet1Eta_=AK4Jets.at(0)->eta;
    AK4Jet1Phi_=AK4Jets.at(0)->phi;
    AK4Jet1Energy_=AK4Jets.at(0)->energy;
  }
  else{
    AK4Jet1Pt_=-999;
    AK4Jet1Eta_=-999;
    AK4Jet1Phi_=-999;
    AK4Jet1Energy_=-999;
  }

  if(nAK4Jets_>1){
    AK4Jet2Pt_=AK4Jets.at(1)->pt;    
    AK4Jet2Eta_=AK4Jets.at(1)->eta;
    AK4Jet2Phi_=AK4Jets.at(1)->phi;
    AK4Jet2Energy_=AK4Jets.at(1)->energy;
  }
  else{
    AK4Jet2Pt_=-999;
    AK4Jet2Eta_=-999;
    AK4Jet2Phi_=-999;
    AK4Jet2Energy_=-999;
  }

  DilepMass_ = DilepMasstemp;
  nMu_= nMu;
  tree->Fill();

}
