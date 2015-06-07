#ifndef TreeMaker_h
#define TreeMaker_h

#include "TTree.h"
#include "TreeReader.h"
#include "TLepton.h"
#include "TJet.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

class TreeMaker {

 public:

  //constructor and destructor
  TreeMaker();
  virtual ~TreeMaker();

  //TTree
  TTree* tree;

  //variables for tree
  float Lep1Pt_;
  float Lep1Eta_;
  float Lep1Phi_;
  float Lep1Energy_;
  int Lep1Flavor_;
  int Lep1Charge_;
  int Lep1Loose_;
  int Lep1Tight_;

  float Lep2Pt_;
  float Lep2Eta_;
  float Lep2Phi_;
  float Lep2Energy_;
  int Lep2Flavor_;
  int Lep2Charge_;
  int Lep2Loose_;
  int Lep2Tight_;

  //int NTightLeptons_;
  int nAK4Jets_;

  float AK4HT_;
  float MET_;

  float AK4Jet1Pt_;
  float AK4Jet1Eta_;
  float AK4Jet1Phi_;
  float AK4Jet1Energy_;

  float AK4Jet2Pt_;
  float AK4Jet2Eta_;
  float AK4Jet2Phi_;
  float AK4Jet2Energy_;


  //functions
  //WriteHists(TreeReader* tr, TTree* t, std::vector<TLepton*> vSSLep);
  void InitTree(std::string treename);
  void FillTree(std::vector<TLepton*> vSSLep, std::vector<TJet*> AK4jets, float HTtemp, float METtemp);

};


#endif
