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
  tree->Branch("nTL",&nTL_);
  tree->Branch("Lep1Pt",&Lep1Pt_);

  //scalefactors
  tree->Branch("trigSF",&trigSF_);
  tree->Branch("IDSF",&IDSF_);
  tree->Branch("IsoSF",&IsoSF_);

  tree->Branch("PUWeight",&puweight_);

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
  tree->Branch("nNewConst",&nNewConst_);

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

  //ak4jets
  tree->Branch("AK8Jet1Pt",&AK8Jet1Pt_);
  tree->Branch("AK8Jet1Eta",&AK8Jet1Eta_);
  tree->Branch("AK8Jet1Phi",&AK8Jet1Phi_);
  tree->Branch("AK8Jet1Energy",&AK8Jet1Energy_);
  tree->Branch("AK8Jet1TrimMass",&AK8Jet1TrimMass_);
  tree->Branch("AK8Jet1PruneMass",&AK8Jet1PruneMass_);
  tree->Branch("AK8Jet1SDMass",&AK8Jet1SDMass_);
  tree->Branch("AK8Jet1FiltMass",&AK8Jet1FiltMass_);
  tree->Branch("AK8Jet1Tau1",&AK8Jet1Tau1_);
  tree->Branch("AK8Jet1Tau2",&AK8Jet1Tau2_);
  tree->Branch("AK8Jet1Tau3",&AK8Jet1Tau3_);
  tree->Branch("AK8Jet1Tau21",&AK8Jet1Tau21_);
  tree->Branch("AK8Jet1Tau31",&AK8Jet1Tau31_);
  tree->Branch("AK8Jet1Tau32",&AK8Jet1Tau32_);
  tree->Branch("AK8Jet1SubjetMaxBDisc",&AK8Jet1SubjetMaxBDisc_);

  tree->Branch("AK8Jet2Pt",&AK8Jet2Pt_);
  tree->Branch("AK8Jet2Eta",&AK8Jet2Eta_);
  tree->Branch("AK8Jet2Phi",&AK8Jet2Phi_);
  tree->Branch("AK8Jet2Energy",&AK8Jet2Energy_);
  tree->Branch("AK8Jet2TrimMass",&AK8Jet2TrimMass_);
  tree->Branch("AK8Jet2PruneMass",&AK8Jet2PruneMass_);
  tree->Branch("AK8Jet2SDMass",&AK8Jet2SDMass_);
  tree->Branch("AK8Jet2FiltMass",&AK8Jet2FiltMass_);
  tree->Branch("AK8Jet2Tau1",&AK8Jet2Tau1_);
  tree->Branch("AK8Jet2Tau2",&AK8Jet2Tau2_);
  tree->Branch("AK8Jet2Tau3",&AK8Jet2Tau3_);
  tree->Branch("AK8Jet2Tau21",&AK8Jet2Tau21_);
  tree->Branch("AK8Jet2Tau31",&AK8Jet2Tau31_);
  tree->Branch("AK8Jet2Tau32",&AK8Jet2Tau32_);
  tree->Branch("AK8Jet2SubjetMaxBDisc",&AK8Jet2SubjetMaxBDisc_);



  //cleaned jets
  tree->Branch("nNewCleanAK4Jets",&nNewCleanAK4Jets_);
  tree->Branch("newCleanAK4HT",&newCleanAK4HT_);
  tree->Branch("newCleanAK4Jet1Pt",&newCleanAK4Jet1Pt_);
  tree->Branch("newCleanAK4Jet1Eta",&newCleanAK4Jet1Eta_);
  tree->Branch("newCleanAK4Jet1Phi",&newCleanAK4Jet1Phi_);
  tree->Branch("newCleanAK4Jet1Energy",&newCleanAK4Jet1Energy_);

  tree->Branch("newCleanAK4Jet2Pt",&newCleanAK4Jet2Pt_);
  tree->Branch("newCleanAK4Jet2Eta",&newCleanAK4Jet2Eta_);
  tree->Branch("newCleanAK4Jet2Phi",&newCleanAK4Jet2Phi_);
  tree->Branch("newCleanAK4Jet2Energy",&newCleanAK4Jet2Energy_);  

  tree->Branch("DilepMass",&DilepMass_);
  tree->Branch("AssocMass",&AssocMass_);
  tree->Branch("Channel",&nMu_);
}

void TreeMaker::FillTree(std::vector<TLepton*> vSSLep, std::vector<TJet*> AK4Jets, std::vector<TJet*> cleanAK4Jets,std::vector<TJet*> simpleCleanAK4Jets, float HTtemp, float METtemp, float DilepMasstemp, int nMu, float weight, std::vector<TLepton*> vNonSSLep,float mcweight, float NPWeighttemp, int nTLtemp, float trSF, float idSF, float isoSF, float puwtemp,float amasst, std::vector<TBoostedJet*> AK8Jets,std::vector<TJet*> newCleanAK4Jets_temp){

  weight_=weight;
  NPWeight_=NPWeighttemp;
  nTL_ = nTLtemp;
  if(mcweight>=0) MCWeight_=1;
  else MCWeight_=-1;

  trigSF_=trSF;
  IDSF_ = idSF;
  IsoSF_ = isoSF;
  puweight_=puwtemp;

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

  //if(Lep2Pt_<20) std::cout<<"Lep2Pt "<<vSSLep.at(1)->pt<<std::endl;

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


  //ak8jets
  int nAK8Jets_ = AK8Jets.size();
  //make tagged ak8 jets
  std::vector<TBoostedJet*> taggedAK8Jets;
  for(int i=0; i<nAK8Jets_; i++){
    if(AK8Jets.at(i)->isWTag() || AK8Jets.at(i)->isTopTag_BTag()) taggedAK8Jets.push_back(AK8Jets.at(i));
  }

  int nTaggedAK8Jets_ = taggedAK8Jets.size();

  //new clean ak4 jets
  std::vector<TJet*> newCleanAK4Jets;
  for(unsigned int i=0; i<newCleanAK4Jets_temp.size(); i++){
    bool save = true;
    TJet* jet = newCleanAK4Jets_temp.at(i);
    for(int j=0; j<nTaggedAK8Jets_; j++){
      float dR = pow( pow(jet->eta - taggedAK8Jets.at(j)->eta,2) + pow(jet->phi - taggedAK8Jets.at(j)->phi, 2), 0.5);
      if(dR < 0.8){
	save=false;
      }
    }
    if(save) newCleanAK4Jets.push_back(jet);
  }
 
  if(nTaggedAK8Jets_>0){
    AK8Jet1Pt_=taggedAK8Jets.at(0)->pt;    
    AK8Jet1Eta_=taggedAK8Jets.at(0)->eta;
    AK8Jet1Phi_=taggedAK8Jets.at(0)->phi;
    AK8Jet1Energy_=taggedAK8Jets.at(0)->energy;
    AK8Jet1TrimMass_=taggedAK8Jets.at(0)->trimmedMass;
    AK8Jet1PruneMass_=taggedAK8Jets.at(0)->prunedMass;
    AK8Jet1SDMass_=taggedAK8Jets.at(0)->softDropMass;
    AK8Jet1FiltMass_=taggedAK8Jets.at(0)->filteredMass;
    AK8Jet1Tau1_ = taggedAK8Jets.at(0)->tau1;
    AK8Jet1Tau2_ = taggedAK8Jets.at(0)->tau2;
    AK8Jet1Tau3_ = taggedAK8Jets.at(0)->tau3;
    AK8Jet1Tau21_ = taggedAK8Jets.at(0)->tau2/taggedAK8Jets.at(0)->tau1;
    AK8Jet1Tau31_ = taggedAK8Jets.at(0)->tau3/taggedAK8Jets.at(0)->tau1;
    AK8Jet1Tau32_ = taggedAK8Jets.at(0)->tau3/taggedAK8Jets.at(0)->tau2;
    float maxBDisc1=-2;
    for(int ib=0; ib<taggedAK8Jets.at(0)->nSubjets; ib++){
      if(taggedAK8Jets.at(0)->subjetBDisc.at(ib) >= maxBDisc1) maxBDisc1=taggedAK8Jets.at(0)->subjetBDisc.at(ib);
    }
    AK8Jet1SubjetMaxBDisc_ = maxBDisc1;
  }
  else{
    AK8Jet1Pt_=-999;
    AK8Jet1Eta_=-999;
    AK8Jet1Phi_=-999;
    AK8Jet1Energy_=-999;
    AK8Jet1TrimMass_=-999;
    AK8Jet1PruneMass_=-999;
    AK8Jet1SDMass_=-999;
    AK8Jet1FiltMass_=-999;
    AK8Jet1Tau1_ = -999;
    AK8Jet1Tau2_ = -999;
    AK8Jet1Tau3_ = -999;
    AK8Jet1Tau21_ = -999;
    AK8Jet1Tau31_ = -999;
    AK8Jet1Tau32_ = -999;
    AK8Jet1SubjetMaxBDisc_ =-999;
  }

  if(nTaggedAK8Jets_>1){
    AK8Jet2Pt_=taggedAK8Jets.at(1)->pt;    
    AK8Jet2Eta_=taggedAK8Jets.at(1)->eta;
    AK8Jet2Phi_=taggedAK8Jets.at(1)->phi;
    AK8Jet2Energy_=taggedAK8Jets.at(1)->energy;
    AK8Jet2TrimMass_=taggedAK8Jets.at(1)->trimmedMass;
    AK8Jet2PruneMass_=taggedAK8Jets.at(1)->prunedMass;
    AK8Jet2SDMass_=taggedAK8Jets.at(1)->softDropMass;
    AK8Jet2FiltMass_=taggedAK8Jets.at(1)->filteredMass;
    AK8Jet2Tau1_ = taggedAK8Jets.at(1)->tau1;
    AK8Jet2Tau2_ = taggedAK8Jets.at(1)->tau2;
    AK8Jet2Tau3_ = taggedAK8Jets.at(1)->tau3;
    AK8Jet2Tau21_ = taggedAK8Jets.at(1)->tau2/taggedAK8Jets.at(1)->tau1;
    AK8Jet2Tau31_ = taggedAK8Jets.at(1)->tau3/taggedAK8Jets.at(1)->tau1;
    AK8Jet2Tau32_ = taggedAK8Jets.at(1)->tau3/taggedAK8Jets.at(1)->tau2;
    float maxBDisc=-2;
    for(int ib=0; ib<taggedAK8Jets.at(1)->nSubjets; ib++){
      if(taggedAK8Jets.at(1)->subjetBDisc.at(ib) >= maxBDisc) maxBDisc=taggedAK8Jets.at(1)->subjetBDisc.at(ib);
    }
    AK8Jet2SubjetMaxBDisc_ = maxBDisc;
  }
  else{
    AK8Jet2Pt_=-999;
    AK8Jet2Eta_=-999;
    AK8Jet2Phi_=-999;
    AK8Jet2Energy_=-999;
    AK8Jet2TrimMass_=-999;
    AK8Jet2PruneMass_=-999;
    AK8Jet2SDMass_=-999;
    AK8Jet2FiltMass_=-999;
    AK8Jet2Tau1_ = -999;
    AK8Jet2Tau2_ = -999;
    AK8Jet2Tau3_ = -999;
    AK8Jet2Tau21_ = -999;
    AK8Jet2Tau31_ = -999;
    AK8Jet2Tau32_ = -999;
    AK8Jet2SubjetMaxBDisc_ =-999;
  }

  //new newCleaned ak4 jets
  nNewCleanAK4Jets_ = newCleanAK4Jets.size();
  //new nConst
  nNewConst_ = newCleanAK4Jets.size() + vNonSSLep.size();
  newCleanAK4HT_=Lep1Pt_+Lep2Pt_;
  for(int i=0; i<nNewCleanAK4Jets_;i++){
    newCleanAK4HT_+=newCleanAK4Jets.at(i)->pt;
  }
  for(unsigned int ilep=0; ilep < vNonSSLep.size(); ilep++){
    newCleanAK4HT_+=vNonSSLep.at(ilep)->pt;
  }
  for(int i=0; i<nTaggedAK8Jets_;i++){
    if(taggedAK8Jets.at(i)->isTopTag_BTag() || taggedAK8Jets.at(i)->isWTag()){
      newCleanAK4HT_+=taggedAK8Jets.at(i)->pt;
    }
    if(taggedAK8Jets.at(i)->isTopTag_BTag()) nNewConst_= nNewConst_+3;
    else if(taggedAK8Jets.at(i)->isWTag() && !taggedAK8Jets.at(i)->isTopTag_BTag()) nNewConst_ = nNewConst_+2;
  }
  
  if(nNewCleanAK4Jets_>0){
    newCleanAK4Jet1Pt_=newCleanAK4Jets.at(0)->pt;    
    newCleanAK4Jet1Eta_=newCleanAK4Jets.at(0)->eta;
    newCleanAK4Jet1Phi_=newCleanAK4Jets.at(0)->phi;
    newCleanAK4Jet1Energy_=newCleanAK4Jets.at(0)->energy;
  }
  else{
    newCleanAK4Jet1Pt_=-999;
    newCleanAK4Jet1Eta_=-999;
    newCleanAK4Jet1Phi_=-999;
    newCleanAK4Jet1Energy_=-999;
  }

  if(nNewCleanAK4Jets_>1){
    newCleanAK4Jet2Pt_=newCleanAK4Jets.at(1)->pt;    
    newCleanAK4Jet2Eta_=newCleanAK4Jets.at(1)->eta;
    newCleanAK4Jet2Phi_=newCleanAK4Jets.at(1)->phi;
    newCleanAK4Jet2Energy_=newCleanAK4Jets.at(1)->energy;
  }
  else{
    newCleanAK4Jet2Pt_=-999;
    newCleanAK4Jet2Eta_=-999;
    newCleanAK4Jet2Phi_=-999;
    newCleanAK4Jet2Energy_=-999;
  }


  nConst_=nCleanAK4Jets_+vNonSSLep.size();
  DilepMass_ = DilepMasstemp;
  AssocMass_ = amasst;
  nMu_= nMu;
  tree->Fill();

}
