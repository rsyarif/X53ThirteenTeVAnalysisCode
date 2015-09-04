#include "../interface/TreeReader.h"

TreeReader::TreeReader(const TString &filename,bool mc)
{

  TFile *f = new TFile(filename);
  f->cd();
  TTree *treetemp = (TTree*)gDirectory->Get("ljmet");
  isMc=mc;
  Init(treetemp);

}

TreeReader::TreeReader(TTree *treetemp,bool mc)
{
  isMc=mc;
  Init(treetemp);
}
TreeReader::~TreeReader(){

}
//need to actually get the data
Int_t TreeReader::GetEntry(Long64_t entry){
  //delete anything hanging out in memory
  for (unsigned int i = 0;i<allMuons.size();++i ) delete allMuons[i];
  for (unsigned int i = 0;i<allElectrons.size();++i ) delete allElectrons[i];
  for (unsigned int i = 0;i<allAK4Jets.size();++i ) delete allAK4Jets[i];
  if(isMc){
    for (unsigned int i = 0;i<genJets.size();++i ) delete genJets[i];
    for (unsigned int i = 0;i<genParticles.size();++i ) delete genParticles[i];
  }

  allMuons.clear();
  goodMuons.clear();
  allElectrons.clear();
  goodElectrons.clear();
  cmsdasElectrons.clear();
  allAK4Jets.clear();
  cleanedAK4Jets.clear();
  if(isMc){
    genJets.clear();
    genParticles.clear();
  }

  //check to make sure not empty
  if (!tree) return 0;  

  int stat =  tree->GetEntry(entry);
  unsigned int nMuons = muPt->size();
  unsigned int nElectrons = elPt->size();
  unsigned int nAK4Jets = AK4JetPt->size();

  for(unsigned int i=0; i<nElectrons;i++){
    allElectrons.push_back(new TElectron((*elPt)[i],(*elEta)[i],(*elPhi)[i],(*elEnergy)[i],(*elCharge)[i],(*elDeta)[i],(*elDphi)[i],(*elDZ)[i],(*elD0)[i],(*elHoE)[i],(*elMHits)[i],(*elOoemoop)[i],(*elSihih)[i],(*elRelIso)[i],(*elPassConversionVeto)[i],(*elChargeConsistent)[i]));
  }

  for(unsigned int i=0; i<nMuons;i++){
    allMuons.push_back(new TMuon((*muPt)[i],
				 (*muEta)[i], (*muPhi)[i], (*muEnergy)[i],(*muCharge)[i], (*muIsLoose)[i],(*muIsTight)[i],
				 (*muGlobal)[i],(*muPF)[i],(*muTracker)[i],(*muChi2)[i], (*muNValMuHits)[i],  (*muNMatchedStations)[i],
				 (*muDxy)[i], (*muDz)[i],(*muNValPixelHits)[i],(*muNTrackerLayers)[i],(*muRelIso)[i]));
  }

  for (unsigned int i=0;i<nAK4Jets; i++){
    //require jet to be greater than 30 GeV and eta less than 2.4
    if( ( (*AK4JetPt)[i]<30) || fabs((*AK4JetEta)[i])>2.4) continue;
    allAK4Jets.push_back(new TJet( (*AK4JetPt)[i], (*AK4JetEta)[i], (*AK4JetPhi)[i],(*AK4JetEnergy)[i]) );
  }

  if(isMc){
    unsigned int ngenJets = genJetPt->size();
    for (unsigned int i=0;i<ngenJets; i++){
      genJets.push_back(new TJet( (*genJetPt)[i], (*genJetEta)[i], (*genJetPhi)[i],(*genJetEnergy)[i]) );
    }
    
    
    //make genparticle collection
    for(unsigned int i=0; i< genPt->size() ; i++){
      genParticles.push_back(new TGenParticle( (*genPt)[i], (*genEta)[i], (*genPhi)[i],(*genEnergy)[i],(*genStatus)[i], (*genId)[i], (*genMotherId)[i]));
    }
  }

  //now from allMuons make goodMuons

  for(unsigned int imu =0; imu<allMuons.size(); imu++){
    if(allMuons.at(imu)->cutBasedTight()) goodMuons.push_back(allMuons.at(imu));
  }

  //now from allElectrons make goodElectrons
  for(unsigned int iel=0; iel< allElectrons.size(); iel++){
    if(allElectrons.at(iel)->cutBasedTight()) goodElectrons.push_back(allElectrons.at(iel));
  }
  //now from allElectrons make cmsdasElectrons
  for(unsigned int iel=0; iel< allElectrons.size(); iel++){
    if(allElectrons.at(iel)->CMSDASTight()) cmsdasElectrons.push_back(allElectrons.at(iel));
  }

  //make clean jets collection
  for(unsigned int ijet=0; ijet<allAK4Jets.size();ijet++){
    TJet* jet = allAK4Jets.at(ijet);
    TLorentzVector cleanLV= jet->lv;

    //clean any tight electrons from the jet
    for(unsigned int iel=0; iel<goodElectrons.size(); iel++){
      TElectron* el = goodElectrons.at(iel);
      float deltaR = pow( pow( jet->eta - el->eta,2) + pow( jet->phi - el->phi,2), 0.5);
      if(deltaR <0.4) cleanLV= cleanLV - el->lv;
    }
    //clean any tight muons from the jet
    for(unsigned int imu=0; imu<goodMuons.size(); imu++){
      TMuon* mu = goodMuons.at(imu);
      float deltaR = pow( pow( jet->eta - mu->eta,2) + pow( jet->phi - mu->phi,2), 0.5);
      if(deltaR <0.4) cleanLV= cleanLV - mu->lv;
    }

    cleanedAK4Jets.push_back(new TJet(cleanLV.Pt(),cleanLV.Eta(),cleanLV.Phi(),cleanLV.Energy()));

  }


  return stat;
}


void TreeReader::Init(TTree *treetemp)
{

  if (!treetemp) return;

  tree=treetemp;

  //intialize vectors to 0 because ROOT
  elD0 = 0;
  elDZ = 0;
  elDeta = 0;
  elDphi = 0;
  elDxy = 0;
  elEnergy = 0;
  elEta = 0;
  elHoE = 0;
  elOoemoop = 0;
  elPhi = 0;
  elPt = 0;
  elRelIso = 0;
  elSihih = 0;
  elChargeConsistent = 0;
  elCharge = 0;
  elIsEBEE = 0;
  elMHits = 0;
  elPassConversionVeto = 0;
  elQuality = 0;
  elVtxFitConv = 0;

  //gen particles
  genEnergy = 0;
  genEta = 0;
  genPhi = 0;
  genPt = 0;
  genId = 0;
  genIndex = 0;
  genMotherId = 0;
  genMotherIndex = 0;
  genStatus = 0;

  //muons
  muChi2 = 0;
  muDxy = 0;
  muDz = 0;
  muEnergy = 0;
  muEta = 0;
  muPhi = 0;
  muPt = 0;
  muRelIso = 0;
  muCharge = 0;
  muGlobal = 0;
  muPF     = 0;
  muTracker =0;
  muNMatchedStations = 0;
  muNTrackerLayers = 0;
  muNValMuHits = 0;
  muNValPixelHits = 0;
  muIsTight = 0;
  muIsLoose = 0;

  //ak4 jets
  AK4JetEnergy = 0;
  AK4JetEta = 0;
  AK4JetPhi = 0;
  AK4JetPt = 0;

  if(isMc){
    //gen jets
    genJetEnergy = 0;
    genJetEta = 0;
    genJetPhi = 0;
    genJetPt = 0;
  }

  //Electrons                                                                                                                                                                                                     
  tree->SetBranchAddress("elChargeConsistent_DileptonCalc", &elChargeConsistent, &b_elChargeConsistent_DileptonCalc);
  tree->SetBranchAddress("elCharge_DileptonCalc", &elCharge, &b_elCharge_DileptonCalc);
  tree->SetBranchAddress("elIsEBEE_DileptonCalc", &elIsEBEE, &b_elIsEBEE_DileptonCalc);
  tree->SetBranchAddress("elMHits_DileptonCalc", &elMHits, &b_elMHits_DileptonCalc);
  tree->SetBranchAddress("elVtxFitConv_DileptonCalc", &elPassConversionVeto, &b_elPassConversionVeto_DileptonCalc);
  tree->SetBranchAddress("elQuality_DileptonCalc", &elQuality, &b_elQuality_DileptonCalc);
  tree->SetBranchAddress("elD0_DileptonCalc", &elD0, &b_elD0_DileptonCalc);
  tree->SetBranchAddress("elDZ_DileptonCalc", &elDZ, &b_elDZ_DileptonCalc);
  tree->SetBranchAddress("elDeta_DileptonCalc", &elDeta, &b_elDeta_DileptonCalc);
  tree->SetBranchAddress("elDphi_DileptonCalc", &elDphi, &b_elDphi_DileptonCalc);
  tree->SetBranchAddress("elDxy_DileptonCalc", &elDxy, &b_elDxy_DileptonCalc);
  tree->SetBranchAddress("elEnergy_DileptonCalc", &elEnergy, &b_elEnergy_DileptonCalc);
  tree->SetBranchAddress("elEta_DileptonCalc", &elEta, &b_elEta_DileptonCalc);
  tree->SetBranchAddress("elHoE_DileptonCalc", &elHoE, &b_elHoE_DileptonCalc);
  tree->SetBranchAddress("elOoemoop_DileptonCalc", &elOoemoop, &b_elOoemoop_DileptonCalc);
  tree->SetBranchAddress("elPhi_DileptonCalc", &elPhi, &b_elPhi_DileptonCalc);
  tree->SetBranchAddress("elPt_DileptonCalc", &elPt, &b_elPt_DileptonCalc);
  tree->SetBranchAddress("elRelIso_DileptonCalc", &elRelIso, &b_elRelIso_DileptonCalc);
  tree->SetBranchAddress("elSihih_DileptonCalc", &elSihih, &b_elSihih_DileptonCalc);

  //Muons                                                                                                                                                                                                         
  tree->SetBranchAddress("muCharge_DileptonCalc", &muCharge, &b_muCharge_DileptonCalc);
  tree->SetBranchAddress("muGlobal_DileptonCalc", &muGlobal, &b_muGlobal_DileptonCalc);
  tree->SetBranchAddress("muPF_DileptonCalc", &muPF, &b_muPF_DileptonCalc);
  tree->SetBranchAddress("muTracker_DileptonCalc", &muTracker, &b_muTracker_DileptonCalc);
  tree->SetBranchAddress("muNMatchedStations_DileptonCalc", &muNMatchedStations, &b_muNMatchedStations_DileptonCalc);
  tree->SetBranchAddress("muNTrackerLayers_DileptonCalc", &muNTrackerLayers, &b_muNTrackerLayers_DileptonCalc);
  tree->SetBranchAddress("muNValMuHits_DileptonCalc", &muNValMuHits, &b_muNValMuHits_DileptonCalc);
  tree->SetBranchAddress("muNValPixelHits_DileptonCalc", &muNValPixelHits, &b_muNValPixelHits_DileptonCalc);
  tree->SetBranchAddress("muChi2_DileptonCalc", &muChi2, &b_muChi2_DileptonCalc);
  tree->SetBranchAddress("muDxy_DileptonCalc", &muDxy, &b_muDxy_DileptonCalc);
  tree->SetBranchAddress("muDz_DileptonCalc", &muDz, &b_muDz_DileptonCalc);
  tree->SetBranchAddress("muEnergy_DileptonCalc", &muEnergy, &b_muEnergy_DileptonCalc);
  tree->SetBranchAddress("muEta_DileptonCalc", &muEta, &b_muEta_DileptonCalc);
  tree->SetBranchAddress("muPhi_DileptonCalc", &muPhi, &b_muPhi_DileptonCalc);
  tree->SetBranchAddress("muPt_DileptonCalc", &muPt, &b_muPt_DileptonCalc);
  tree->SetBranchAddress("muRelIso_DileptonCalc", &muRelIso, &b_muRelIso_DileptonCalc);
  tree->SetBranchAddress("muIsTight_DileptonCalc",&muIsTight,&b_muIsTight_DileptonCalc);
  tree->SetBranchAddress("muIsLoose_DileptonCalc",&muIsLoose,&b_muIsLoose_DileptonCalc);

  //ak4 jets
  tree->SetBranchAddress("AK4JetEnergy_DileptonCalc", &AK4JetEnergy, &b_AK4JetEnergy_DileptonCalc);
  tree->SetBranchAddress("AK4JetEta_DileptonCalc", &AK4JetEta, &b_AK4JetEta_DileptonCalc);
  tree->SetBranchAddress("AK4JetPhi_DileptonCalc", &AK4JetPhi, &b_AK4JetPhi_DileptonCalc);
  tree->SetBranchAddress("AK4JetPt_DileptonCalc", &AK4JetPt, &b_AK4JetPt_DileptonCalc);

  if(isMc){
    //gen jets
    tree->SetBranchAddress("genJetEnergy_DileptonCalc", &genJetEnergy, &b_genJetEnergy_DileptonCalc);
    tree->SetBranchAddress("genJetEta_DileptonCalc", &genJetEta, &b_genJetEta_DileptonCalc);
    tree->SetBranchAddress("genJetPhi_DileptonCalc", &genJetPhi, &b_genJetPhi_DileptonCalc);
    tree->SetBranchAddress("genJetPt_DileptonCalc", &genJetPt, &b_genJetPt_DileptonCalc);
    
    //Gen Info                                                                                                                                                                                                      
    tree->SetBranchAddress("genID_DileptonCalc", &genId, &b_genID_DileptonCalc);
    tree->SetBranchAddress("genIndex_DileptonCalc", &genIndex, &b_genIndex_DileptonCalc);
    tree->SetBranchAddress("genMotherID_DileptonCalc", &genMotherId, &b_genMotherID_DileptonCalc);
    tree->SetBranchAddress("genMotherIndex_DileptonCalc", &genMotherIndex, &b_genMotherIndex_DileptonCalc);
    tree->SetBranchAddress("genStatus_DileptonCalc", &genStatus, &b_genStatus_DileptonCalc);
    
    tree->SetBranchAddress("genEnergy_DileptonCalc", &genEnergy, &b_genEnergy_DileptonCalc);
    tree->SetBranchAddress("genEta_DileptonCalc", &genEta, &b_genEta_DileptonCalc);
    tree->SetBranchAddress("genPhi_DileptonCalc", &genPhi, &b_genPhi_DileptonCalc);
    tree->SetBranchAddress("genPt_DileptonCalc", &genPt, &b_genPt_DileptonCalc);
    //  tree->SetBranchAddress("genCharge_DileptonCalc", &genCharge, &b_genCharge_DileptonCalc);
  }

  //met
  tree->SetBranchAddress("met_DileptonCalc", &MET, &b_MET_DileptonCalc);
  tree->SetBranchAddress("met_phi_DileptonCalc", &MET_phi, &b_MET_phi_DileptonCalc);


  //trigger info
  //double electron
  tree->SetBranchAddress("HLT_DoubleEle33_DileptonCalc", &HLT_DoubleEle33,&b_HLT_DoubleEle33_DileptonCalc);
  tree->SetBranchAddress("HLT_DoubleEle33_MW_DileptonCalc",&HLT_DoubleEle33,&b_HLT_DoubleEle33_MW_DileptonCalc);
  tree->SetBranchAddress("HLT_Ele17_Ele12_DZ_DileptonCalc",&HLT_Ele17Ele12,&b_HLT_Ele17Ele12_DileptonCalc);
  //single electron
  tree->SetBranchAddress("HLT_Ele27WP85_DileptonCalc",&HLT_Ele27WP85,&b_HLT_Ele27WP85_DileptonCalc);
  //double muon
  tree->SetBranchAddress("HLT_Mu27TkMu8_DileptonCalc",&HLT_Mu27TkMu8,&b_HLT_Mu27TkMu8_DileptonCalc);
  tree->SetBranchAddress("HLT_Mu30TkMu11_DileptonCalc",&HLT_Mu30TkMu11,&b_HLT_Mu30TkMu11_DileptonCalc);
  tree->SetBranchAddress("HLT_Mu40TkMu11_DileptonCalc",&HLT_Mu40TkMu11,&b_HLT_Mu40TkMu11_DileptonCalc);
  tree->SetBranchAddress("HLT_DoubleMu33NoFiltersNoVtx_DileptonCalc",&HLT_DoubleMu33NoFiltersNoVtx,&b_HLT_DoubleMu33NoFiltersNoVtx_DileptonCalc);
  //single muon
  tree->SetBranchAddress("HLT_Mu40_DileptonCalc",&HLT_Mu40,&b_HLT_Mu40_DileptonCalc);
  tree->SetBranchAddress("HLT_IsoTkMu24_DileptonCalc",&HLT_IsoTkMu24,&b_HLT_IsoTkMu24_DileptonCalc);
  //cross triggers
  tree->SetBranchAddress("HLT_Mu17Ele12_DileptonCalc",&HLT_Mu17Ele12,&b_HLT_Mu17Ele12_DileptonCalc);
  tree->SetBranchAddress("HLT_Mu8Ele17_DileptonCalc",&HLT_Mu8Ele17,&b_HLT_Mu8Ele17_DileptonCalc);
  tree->SetBranchAddress("HLT_Mu23Ele12_DileptonCalc",&HLT_Mu23Ele12,&b_HLT_Mu23Ele12_DileptonCalc);
  tree->SetBranchAddress("HLT_Mu8Ele23_DileptonCalc",&HLT_Mu8Ele23,&b_HLT_Mu8Ele23_DileptonCalc);
  //hadronic triggers
  tree->SetBranchAddress("HLT_PFHT900_DileptonCalc",&HLT_PFHT900,&b_HLT_PFHT900_DileptonCalc);
  tree->SetBranchAddress("HLT_AK8PFJet360TrimMass30_DileptonCalc",&HLT_AK8PFJet360TrimMass30,&b_HLT_AK8PFJet360TrimMass30_DileptonCalc);



}
