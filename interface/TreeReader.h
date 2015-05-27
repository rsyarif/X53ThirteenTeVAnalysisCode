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
  TreeReader(TTree *tree);
  TreeReader(const TString &filename);
  virtual ~TreeReader();

  //high level collections
  std::vector <TMuon*> allMuons, goodMuons,looseMuons;
  std::vector <TElectron*> allElectrons, goodElectrons, looseElectrons;
  std::vector <TGenParticle*> genParticles;
  std::vector <TJet*> allAK4Jets;
  std::vector <TJet*> genJets;
  TTree* tree;

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
  std::vector<int>     *elIsEBEE;
  TBranch        *b_elIsEBEE_DileptonCalc;
  std::vector<int>     *elMHits;
  TBranch        *b_elMHits_DileptonCalc;
  std::vector<int>     *elNotConversion;
  TBranch        *b_elNotConversion_DileptonCalc;
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
  //Isolation
  std::vector<double>  *elRelIso;
  TBranch        *b_elRelIso_DileptonCalc;

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

  //gen jets
  std::vector<double>  *genJetEnergy;
  TBranch        *b_genJetEnergy_DileptonCalc;
  std::vector<double>  *genJetEta;
  TBranch        *b_genJetEta_DileptonCalc;
  std::vector<double>  *genJetPhi;
  TBranch        *b_genJetPhi_DileptonCalc;
  std::vector<double>  *genJetPt;
  TBranch        *b_genJetPt_DileptonCalc;

};

#endif
