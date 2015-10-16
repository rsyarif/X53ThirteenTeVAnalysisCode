#ifndef TreeReader_h
#define TreeReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include "TLepton.h"
#include "TGenParticle.h"
#include "TElectron.h"
#include "TMuon.h"
#include "TJet.h"
#include <stdio.h>
#include <vector>


class TreeReader{

 public:

  //constructor and desctructor
  TreeReader(TTree *tree,bool mc);
  TreeReader(const TString &filename,bool mc);
  virtual ~TreeReader();

  //high level collections
  std::vector <TMuon*> allMuons, goodMuons,looseMuons;
  std::vector <TElectron*> allElectrons, goodElectrons, looseElectrons, cmsdasElectrons, loose50nsElectrons, good50nsElectrons;
  std::vector <TGenParticle*> genParticles;
  std::vector <TJet*> allAK4Jets,cleanedAK4Jets,simpleCleanedAK4Jets;
  std::vector <TJet*> genJets;

  //met
  double MET;
  TBranch* b_MET_DileptonCalc;
  double MET_phi;
  TBranch* b_MET_phi_DileptonCalc;

  TTree* tree;
  bool isMc;
  //function to get the data
  Int_t GetEntry(Long64_t entry);
  //initialize the tree
  virtual void Init(TTree* treetemp);

  /*collections to get from ljmet trees AND their corresponding branches*/

  //Electrons
  //kinematics
  std::vector<double>  *elPt;
  TBranch        *b_elPt_DileptonCalc;
  std::vector<double>  *elEta;
  TBranch        *b_elEta_DileptonCalc;
  std::vector<double>  *elPhi;
  TBranch        *b_elPhi_DileptonCalc;
  std::vector<double>  *elEnergy;
  TBranch        *b_elEnergy_DileptonCalc;

  std::vector<int>     *elChargeConsistent;
  TBranch        *b_elChargeConsistent_DileptonCalc;
  std::vector<int>     *elCharge;
  TBranch        *b_elCharge_DileptonCalc;
  std::vector<int>     *elGsfCharge;
  TBranch        *b_elGsfCharge_DileptonCalc;
  std::vector<int>     *elCtfCharge;
  TBranch        *b_elCtfCharge_DileptonCalc;
  std::vector<int>     *elScPixCharge;
  TBranch        *b_elScPixCharge_DileptonCalc;
  std::vector<int>     *elIsEBEE;
  TBranch        *b_elIsEBEE_DileptonCalc;
  std::vector<int>     *elMHits;
  TBranch        *b_elMHits_DileptonCalc;
  std::vector<int>     *elPassConversionVeto;
  TBranch        *b_elPassConversionVeto_DileptonCalc;
  std::vector<int>     *elQuality;
  TBranch        *b_elQuality_DileptonCalc;
  std::vector<int>     *elVtxFitConv;
  TBranch        *b_elVtxFitConv_DileptonCalc;
  //track quality variables
  std::vector<double>  *elD0;
  TBranch        *b_elD0_DileptonCalc;
  std::vector<double>  *elDZ;
  TBranch        *b_elDZ_DileptonCalc;
  std::vector<double>  *elDeta;
  TBranch        *b_elDeta_DileptonCalc;
  std::vector<double>  *elDphi;
  TBranch        *b_elDphi_DileptonCalc;
  std::vector<double>  *elDxy;
  TBranch        *b_elDxy_DileptonCalc;
  //electron quality variables
  std::vector<double>  *elHoE;
  TBranch        *b_elHoE_DileptonCalc;
  std::vector<double>  *elOoemoop;
  TBranch        *b_elOoemoop_DileptonCalc; 
  std::vector<double>  *elSihih;
  TBranch        *b_elSihih_DileptonCalc;
  //Isolation Variables
  std::vector<double>  *elchIso;
  TBranch        *b_elchIso_DileptonCalc;
  std::vector<double>  *elpuIso;
  TBranch        *b_elpuIso_DileptonCalc;
  std::vector<double>  *elneutIso;
  TBranch        *b_elneutIso_DileptonCalc;
  std::vector<double>  *elphotIso;
  TBranch        *b_elphotIso_DileptonCalc;
  std::vector<double>  *elrhoIso;
  TBranch        *b_elrhoIso_DileptonCalc;
  std::vector<double>  *elMiniIso;
  TBranch        *b_elMiniIso_DileptonCalc;
  std::vector<double>  *elAEff;
  TBranch        *b_elAEff_DileptonCalc;
  //mva value
  std::vector<double> *elMVA;
  TBranch        *b_elMVA_DileptonCalc;

  //Muons 
  std::vector<int>     *muCharge;
  TBranch        *b_muCharge_DileptonCalc;
  std::vector<bool>     *muGlobal;
  TBranch        *b_muGlobal_DileptonCalc;
  std::vector<bool>     *muPF;
  TBranch        *b_muPF_DileptonCalc;
  std::vector<bool>     *muTracker;
  TBranch        *b_muTracker_DileptonCalc;
  std::vector<int>     *muNMatchedStations;
  TBranch        *b_muNMatchedStations_DileptonCalc;
  std::vector<int>     *muNTrackerLayers;
  TBranch        *b_muNTrackerLayers_DileptonCalc;
  std::vector<int>     *muNValMuHits;
  TBranch        *b_muNValMuHits_DileptonCalc; 
  std::vector<int>     *muNValPixelHits;
  TBranch        *b_muNValPixelHits_DileptonCalc;
  std::vector<double>  *muChi2;
  TBranch        *b_muChi2_DileptonCalc;
  std::vector<double>  *muDxy;
  TBranch        *b_muDxy_DileptonCalc;
  std::vector<double>  *muDz;
  TBranch        *b_muDz_DileptonCalc;
  std::vector<double>  *muEnergy;
  TBranch        *b_muEnergy_DileptonCalc;
  std::vector<double>  *muEta;
  TBranch        *b_muEta_DileptonCalc;
  std::vector<double>  *muPhi;
  TBranch        *b_muPhi_DileptonCalc;
  std::vector<double>  *muPt;
  TBranch        *b_muPt_DileptonCalc; 
  std::vector<double>  *muRelIso;
  TBranch        *b_muRelIso_DileptonCalc;
  std::vector<double>  *muMiniIso;
  TBranch        *b_muMiniIso_DileptonCalc;
  std::vector<int>     *muIsTight;
  TBranch        *b_muIsTight_DileptonCalc;
  std::vector<int>     *muIsLoose;
  TBranch        *b_muIsLoose_DileptonCalc;

  //Gen Particles
  std::vector<int>     *genId;
  TBranch        *b_genID_DileptonCalc;
  std::vector<int>     *genIndex;
  TBranch        *b_genIndex_DileptonCalc;
  std::vector<int>     *genMotherId;
  TBranch        *b_genMotherID_DileptonCalc;
  std::vector<int>     *genMotherIndex;
  TBranch        *b_genMotherIndex_DileptonCalc;
  std::vector<int>     *genStatus;
  TBranch        *b_genStatus_DileptonCalc; 
  std::vector<double>  *genEnergy;
  TBranch        *b_genEnergy_DileptonCalc;
  std::vector<double>  *genEta;
  TBranch        *b_genEta_DileptonCalc;
  std::vector<double>  *genPhi;
  TBranch        *b_genPhi_DileptonCalc;
  std::vector<double>  *genPt;
  TBranch        *b_genPt_DileptonCalc; 
  //std::vector<double> *genCharge;
  //TBranch        *b_genCharge_DileptonCalc;
  //ak4 jets
  std::vector<double>  *AK4JetEnergy;
  TBranch        *b_AK4JetEnergy_DileptonCalc;
  std::vector<double>  *AK4JetEta;
  TBranch        *b_AK4JetEta_DileptonCalc;
  std::vector<double>  *AK4JetPhi;
  TBranch        *b_AK4JetPhi_DileptonCalc;
  std::vector<double>  *AK4JetPt;
  TBranch        *b_AK4JetPt_DileptonCalc;

  //get cleaned jets
  std::vector<double>  *cleanedAK4JetEnergy;
  TBranch        *b_cleanedAK4JetEnergy_DileptonCalc;
  std::vector<double>  *cleanedAK4JetEta;
  TBranch        *b_cleanedAK4JetEta_DileptonCalc;
  std::vector<double>  *cleanedAK4JetPhi;
  TBranch        *b_cleanedAK4JetPhi_DileptonCalc;
  std::vector<double>  *cleanedAK4JetPt;
  TBranch        *b_cleanedAK4JetPt_DileptonCalc;

  //gen jets
  std::vector<double>  *genJetEnergy;
  TBranch        *b_genJetEnergy_DileptonCalc;
  std::vector<double>  *genJetEta;
  TBranch        *b_genJetEta_DileptonCalc;
  std::vector<double>  *genJetPhi;
  TBranch        *b_genJetPhi_DileptonCalc;
  std::vector<double>  *genJetPt;
  TBranch        *b_genJetPt_DileptonCalc;

  //MC weight info
  double          MCWeight;
  TBranch*    b_MCWeight_DileptonCalc;


  // Trigger Info
  //double electron
  bool HLT_DoubleEle33;
  TBranch* b_HLT_DoubleEle33_DileptonCalc;
  bool HLT_DoubleEle33_MW;
  TBranch* b_HLT_DoubleEle33_MW_DileptonCalc;
  bool HLT_Ele17Ele12;
  TBranch* b_HLT_Ele17Ele12_DileptonCalc;
  //single electron
  bool HLT_Ele27WP85;
  TBranch* b_HLT_Ele27WP85_DileptonCalc;
  //double muon
  bool HLT_Mu27TkMu8;
  TBranch* b_HLT_Mu27TkMu8_DileptonCalc;
  bool HLT_Mu30TkMu11;
  TBranch* b_HLT_Mu30TkMu11_DileptonCalc;
  bool HLT_Mu40TkMu11;
  TBranch* b_HLT_Mu40TkMu11_DileptonCalc;
  bool HLT_DoubleMu33NoFiltersNoVtx;
  TBranch* b_HLT_DoubleMu33NoFiltersNoVtx_DileptonCalc;
  //single muon
  bool HLT_Mu40;
  TBranch* b_HLT_Mu40_DileptonCalc;
  bool HLT_IsoTkMu24;
  TBranch* b_HLT_IsoTkMu24_DileptonCalc;
  //cross triggers
  bool HLT_Mu17Ele12;
  TBranch* b_HLT_Mu17Ele12_DileptonCalc;
  bool HLT_Mu8Ele17;
  TBranch* b_HLT_Mu8Ele17_DileptonCalc;
  bool HLT_Mu23Ele12;
  TBranch* b_HLT_Mu23Ele12_DileptonCalc;
  bool HLT_Mu8Ele23;
  TBranch* b_HLT_Mu8Ele23_DileptonCalc;
  bool HLT_Mu30Ele30;
  TBranch* b_HLT_Mu30Ele30_DileptonCalc;
  //hadronic triggers
  bool HLT_PFHT900;
  TBranch* b_HLT_PFHT900_DileptonCalc;
  bool HLT_AK8PFJet360TrimMass30;
  TBranch* b_HLT_AK8PFJet360TrimMass30_DileptonCalc;


};

#endif
