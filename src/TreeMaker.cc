#include "../interface/TreeMaker.h"
#include <assert.h>

//constructor
TreeMaker::TreeMaker(){}


//destructor
TreeMaker::~TreeMaker(){}

//Initialize tree
void TreeMaker::InitTree(std::string treename){
  tree = new TTree(treename.c_str(),treename.c_str());

  //weight
  tree->Branch("ChargeMisIDWeight",&weight_);
  tree->Branch("MCWeight",&MCWeight_);
  tree->Branch("NPWeight",&NPWeight_);
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

  //number of constiuents, cleaned ak4 jets and non ssdl leptons
  tree->Branch("nConst",&nConst_);

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


  //cleaned jets
  tree->Branch("nCleanAK4Jets",&nCleanAK4Jets_);
  tree->Branch("cleanAK4HT",&cleanAK4HT_);
  tree->Branch("cleanAK4Jet1Pt",&cleanAK4Jet1Pt_);
  tree->Branch("cleanAK4Jet1Eta",&cleanAK4Jet1Eta_);
  tree->Branch("cleanAK4Jet1Phi",&cleanAK4Jet1Phi_);
  tree->Branch("cleanAK4Jet1Energy",&cleanAK4Jet1Energy_);

  tree->Branch("cleanAK4Jet2Pt",&cleanAK4Jet2Pt_);
  tree->Branch("cleanAK4Jet2Eta",&cleanAK4Jet2Eta_);
  tree->Branch("cleanAK4Jet2Phi",&cleanAK4Jet2Phi_);
  tree->Branch("cleanAK4Jet2Energy",&cleanAK4Jet2Energy_);  

  //simple cleaned jets
  tree->Branch("nSimpleCleanAK4Jets",&nSimpleCleanAK4Jets_);
  tree->Branch("simpleCleanAK4HT",&simpleCleanAK4HT_);
  tree->Branch("simpleCleanAK4Jet1Pt",&simpleCleanAK4Jet1Pt_);
  tree->Branch("simpleCleanAK4Jet1Eta",&simpleCleanAK4Jet1Eta_);
  tree->Branch("simpleCleanAK4Jet1Phi",&simpleCleanAK4Jet1Phi_);
  tree->Branch("simpleCleanAK4Jet1Energy",&simpleCleanAK4Jet1Energy_);

  tree->Branch("simpleCleanAK4Jet2Pt",&simpleCleanAK4Jet2Pt_);
  tree->Branch("simpleCleanAK4Jet2Eta",&simpleCleanAK4Jet2Eta_);
  tree->Branch("simpleCleanAK4Jet2Phi",&simpleCleanAK4Jet2Phi_);
  tree->Branch("simpleCleanAK4Jet2Energy",&simpleCleanAK4Jet2Energy_);  


  tree->Branch("DilepMass",&DilepMass_);
  tree->Branch("Channel",&nMu_);
}

void TreeMaker::FillTree(std::vector<TLepton*> vSSLep, std::vector<TJet*> AK4Jets, std::vector<TJet*> cleanAK4Jets,std::vector<TJet*> simpleCleanAK4Jets, float HTtemp, float METtemp, float DilepMasstemp, int nMu, float weight, std::vector<TLepton*> vNonSSLep,float mcweight, float NPWeighttemp){

  weight_=weight;
  NPWeight_=NPWeighttemp;
  if(mcweight>0) MCWeight_=1;
  else MCWeight_=-1;
  
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
  AK4HT_+=Lep1Pt_+Lep2Pt_;
  for(unsigned int ilep=0; ilep < vNonSSLep.size(); ilep++){
    AK4HT_+=vNonSSLep.at(ilep)->pt;
  }
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


  //cleaned jets
  nCleanAK4Jets_ = cleanAK4Jets.size();
  cleanAK4HT_=Lep1Pt_+Lep2Pt_;
  for(int i=0; i<nCleanAK4Jets_;i++){
    cleanAK4HT_+=cleanAK4Jets.at(i)->pt;
  }
  for(unsigned int ilep=0; ilep < vNonSSLep.size(); ilep++){
    cleanAK4HT_+=vNonSSLep.at(ilep)->pt;
  }

  if(nCleanAK4Jets_>0){
    cleanAK4Jet1Pt_=cleanAK4Jets.at(0)->pt;    
    cleanAK4Jet1Eta_=cleanAK4Jets.at(0)->eta;
    cleanAK4Jet1Phi_=cleanAK4Jets.at(0)->phi;
    cleanAK4Jet1Energy_=cleanAK4Jets.at(0)->energy;
  }
  else{
    cleanAK4Jet1Pt_=-999;
    cleanAK4Jet1Eta_=-999;
    cleanAK4Jet1Phi_=-999;
    cleanAK4Jet1Energy_=-999;
  }

  if(nCleanAK4Jets_>1){
    cleanAK4Jet2Pt_=cleanAK4Jets.at(1)->pt;    
    cleanAK4Jet2Eta_=cleanAK4Jets.at(1)->eta;
    cleanAK4Jet2Phi_=cleanAK4Jets.at(1)->phi;
    cleanAK4Jet2Energy_=cleanAK4Jets.at(1)->energy;
  }
  else{
    cleanAK4Jet2Pt_=-999;
    cleanAK4Jet2Eta_=-999;
    cleanAK4Jet2Phi_=-999;
    cleanAK4Jet2Energy_=-999;
  }

  //cleaned jets
  nSimpleCleanAK4Jets_ = simpleCleanAK4Jets.size();
  simpleCleanAK4HT_=Lep1Pt_+Lep2Pt_;
  for(int i=0; i<nSimpleCleanAK4Jets_;i++){
    simpleCleanAK4HT_+=simpleCleanAK4Jets.at(i)->pt;
  }
  for(unsigned int ilep=0; ilep < vNonSSLep.size(); ilep++){
    AK4HT_+=vNonSSLep.at(ilep)->pt;
  }

  if(nSimpleCleanAK4Jets_ >0){
    //std::cout<<"filling cleaned jet 0 "<<std::endl;
    simpleCleanAK4Jet1Pt_=simpleCleanAK4Jets.at(0)->pt;    
    simpleCleanAK4Jet1Eta_=simpleCleanAK4Jets.at(0)->eta;
    simpleCleanAK4Jet1Phi_=simpleCleanAK4Jets.at(0)->phi;
    simpleCleanAK4Jet1Energy_=simpleCleanAK4Jets.at(0)->energy;
  }
  else{
    simpleCleanAK4Jet1Pt_=-999;
    simpleCleanAK4Jet1Eta_=-999;
    simpleCleanAK4Jet1Phi_=-999;
    simpleCleanAK4Jet1Energy_=-999;
  }

  if(nSimpleCleanAK4Jets_>1){
    simpleCleanAK4Jet2Pt_=simpleCleanAK4Jets.at(1)->pt;    
    simpleCleanAK4Jet2Eta_=simpleCleanAK4Jets.at(1)->eta;
    simpleCleanAK4Jet2Phi_=simpleCleanAK4Jets.at(1)->phi;
    simpleCleanAK4Jet2Energy_=simpleCleanAK4Jets.at(1)->energy;
  }
  else{
    simpleCleanAK4Jet2Pt_=-999;
    simpleCleanAK4Jet2Eta_=-999;
    simpleCleanAK4Jet2Phi_=-999;
    simpleCleanAK4Jet2Energy_=-999;
  }



  nConst_=nCleanAK4Jets_+vNonSSLep.size();
  DilepMass_ = DilepMasstemp;
  nMu_= nMu;
  tree->Fill();

}
